/*
 MIT License

 Copyright (c) 2018 Anderson Tavares <acmt at outlook.com>

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/
#include <ncz.h>
#include <string.h>
#include <stdlib.h>

#undef ZNZ_MAX_BLOCK_SIZE
#define ZNZ_MAX_BLOCK_SIZE (1<<30)

ncz*
ncz_new(){
  return calloc(1,sizeof(ncz));
}

ncz*
ncz_open(const char* path, const char* mode, uint8_t withz){
  ncz* fp = ncz_new();
  memset(fp, 0, sizeof(ncz));
#ifdef HAVE_ZLIB
  fp->withz = withz;
  if (withz) {
    if((fp->gzf = gzopen(path,mode)) == NULL) {
      free(fp);
      return NULL;
    }
  } else {
#endif
    if((fp->nczf = fopen(path,mode)) == NULL) {
      free(fp);
      return NULL;
    }
#ifdef HAVE_ZLIB
  }
#endif

  return fp;
}

int
ncz_close(ncz* fp){
  int retval = 0;

  if (fp != NULL) {
#ifdef HAVE_ZLIB
    if (fp->gzf!=NULL)  { retval = gzclose(fp->gzf); }
#endif
    if (fp->nczf!=NULL) { retval = fclose(fp->nczf); }

    free(fp);
  }
  return retval;
}

size_t
ncz_read(ncz* fp,void* buf, size_t size, size_t nmemb){
  size_t     remain = size*nmemb;
  uint32_t   nread;
  uint32_t   n2read;
  char     * cbuf = (char *)buf;
  if (fp == NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (fp->gzf!=NULL) {
    /* gzread/write take unsigned int length, so maybe read in int pieces
       (noted by M Hanke, example given by M Adler)   6 July 2010 [rickr] */
    while( remain > 0 ) {
       n2read = (remain < ZNZ_MAX_BLOCK_SIZE) ? remain : ZNZ_MAX_BLOCK_SIZE;
       nread = gzread(fp->gzf, (void *)cbuf, n2read);
       if( nread < 0 ) return nread; /* returns -1 on error */

       remain -= nread;
       cbuf += nread;

       /* require reading n2read bytes, so we don't get stuck */
       if( nread < (int)n2read ) break;  /* return will be short */
    }

    /* warn of a short read that will seem complete */
    if( remain > 0 && remain < size )
       fprintf(stderr,"** znzread: read short by %u bytes\n",(unsigned)remain);

    return nmemb - remain/size;   /* return number of members processed */
  }
#endif
  return fread(buf,size,nmemb,fp->nczf);
}

size_t
ncz_write(ncz* fp, const void* buf, size_t size, size_t nmemb){
  size_t     remain = size*nmemb;
  const char * cbuf = (const char *)buf;
  unsigned   n2write;
  int        nwritten;
  if (fp==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (fp->gzf!=NULL) {
    while( remain > 0 ) {
      n2write = (remain < ZNZ_MAX_BLOCK_SIZE) ? remain : ZNZ_MAX_BLOCK_SIZE;
      nwritten = gzwrite(fp->gzf, (const void *)cbuf, n2write);

      /* gzread returns 0 on error, but in case that ever changes... */
      if( nwritten < 0 ) return nwritten;

      remain -= nwritten;
      cbuf += nwritten;

      /* require writing n2write bytes, so we don't get stuck */
      if( nwritten < (int)n2write ) break;
    }

    /* warn of a short write that will seem complete */
    if( remain > 0 && remain < size )
      fprintf(stderr,"** znzwrite: write short by %u bytes\n",(unsigned)remain);

    return nmemb - remain/size;   /* return number of members processed */
  }
#endif
  return fwrite(buf,size,nmemb,fp->nczf);
}

long
ncz_seek(ncz* file, long offset, int whence)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return (long) gzseek(file->gzf,offset,whence);
#endif
  return fseek(file->nczf,offset,whence);
}

int
ncz_rewind(ncz* stream)
{
  if (stream==NULL) { return 0; }
#ifdef HAVE_ZLIB
  /* On some systems, gzrewind() fails for uncompressed files.
     Use gzseek(), instead.               10, May 2005 [rickr]
     if (stream->gzf!=NULL) return gzrewind(stream->gzf);
  */

  if (stream->gzf!=NULL) return (int)gzseek(stream->gzf, 0L, SEEK_SET);
#endif
  rewind(stream->nczf);
  return 0;
}

long
ncz_tell(ncz* file)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return (long) gztell(file->gzf);
#endif
  return ftell(file->nczf);
}

int
ncz_puts(ncz* file, const char * str)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return gzputs(file->gzf,str);
#endif
  return fputs(str,file->nczf);
}


char *
ncz_gets(ncz* file, char* str, int size)
{
  if (file==NULL) { return NULL; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return gzgets(file->gzf,str,size);
#endif
  return fgets(str,size,file->nczf);
}


int
ncz_flush(ncz* file)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return gzflush(file->gzf,Z_SYNC_FLUSH);
#endif
  return fflush(file->nczf);
}


int
ncz_eof(ncz* file)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return gzeof(file->gzf);
#endif
  return feof(file->nczf);
}


int
ncz_putc(ncz* file, int c)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return gzputc(file->gzf,c);
#endif
  return fputc(c,file->nczf);
}


int
ncz_getc(ncz* file)
{
  if (file==NULL) { return 0; }
#ifdef HAVE_ZLIB
  if (file->gzf!=NULL) return gzgetc(file->gzf);
#endif
  return fgetc(file->nczf);
}

int
ncz_printf(ncz* stream, const char* format, ...){
  va_list va;
  char   *tmpstr;
  int     retval=0;
  size_t  size;
  if (stream==NULL) { return 0; }
  va_start(va, format);
#ifdef HAVE_ZLIB
  if (stream->gzf!=NULL) {
    size   = strlen(format) + (1<<16);
    tmpstr = malloc(size);
    vsprintf(tmpstr,format,va);
    retval = gzprintf(stream->gzf,"%s",tmpstr);
    free(tmpstr);
  } else {
#endif
   retval  = vfprintf(stream->nczf,format,va);
#ifdef HAVE_ZLIB
  }
#endif
  va_end(va);
  return retval;
}
