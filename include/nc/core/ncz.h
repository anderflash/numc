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
#ifndef NC_CORE_NCZ_H
#define NC_CORE_NCZ_H
#include <stdio.h>
#include <zlib.h>
#include <stdint.h>
typedef struct ncz {
  FILE* nczf;
#ifdef HAVE_ZLIB
  gzFile gzf;
#endif
  uint8_t withz;
} ncz;

ncz*
ncz_open(const char* path, const char *mode, uint8_t withz);
int
ncz_close(ncz *fp);
size_t
ncz_read(ncz *fp, void* buf, size_t size, size_t nmemb);
size_t
ncz_write(ncz *fp, const void *buf, size_t size, size_t nmemb);
long
ncz_seek(ncz *fp, long offset, int whence);
long
ncz_tell(ncz *fp);
int
ncz_puts(ncz *fp, const char *str);
int
ncz_rewind(ncz *fp);
char*
ncz_gets(ncz *fp, char *str, int size);
int
ncz_flush(ncz *fp);
int
ncz_eof(ncz *fp);
int
ncz_putc(ncz *fp, int c);
int
ncz_getc(ncz *fp);
int
ncz_printf(ncz *fp, const char* format, ...);

#endif
