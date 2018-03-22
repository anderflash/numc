#include <nc/img.h>
#include <inttypes.h>
static void
pgm_skip_comm(char* s, size_t m, FILE* fp){
  while(fgets(s,m,fp) != NULL)
    if(s[0]!='#' && s[0]!='\n') break;
}

au8*
au8_read_pgm(char *filename) {

}

au16*
au16_read_pgm(char *filename) {
  FILE* fp;
  char version[4];
  au16*    array = NULL;
  uint64_t i;
  uint64_t max_gray;
  nelem_t shape[3];
  uint64_t nelem;
  uint32_t width, height;
  uint16_t dim;
  uint16_t* data;

  char     line[256];

  fp = fopen(filename,"rb");
  if(!fp){
    // at_error_set(error, "[at_array_read_ppm_pgm] File %s could not be opened for reading", filename);
    return NULL;
  }
  fgets(version, sizeof(version), fp);


  if(version[0] == 'P' && (version[1] == '5' || version[1] == '2' || version[1] == '6')){
    if(version[1] == '6') dim = 3;
    else                  dim = 2;
    pgm_skip_comm(line,256,fp);
    sscanf(line, "%d %d\n", &width, &height);
    pgm_skip_comm(line,256,fp);
    sscanf(line, "%lu", &max_gray);

    shape[0]     = height;
    shape[1]     = width;
    shape[2]     = 3;
    array        = au16_new_shape(dim, shape);
    data         = array->d;
    nelem        = array->h.n;
    if(version[1] == '2')
      for(i = 0; i < nelem; i++)
        fscanf(fp, "%"SCNu16, &data[i]);
    else
      fread(data, sizeof(uint16_t), nelem,fp);
  }else{
    // at_error_set(error, "[at_array_read_ppm_pgm] File %s could not be opened for reading", filename);
  }
  fclose(fp);
  return array;
}

void
au16_write_pgm(au16* a, char* filename) {
  FILE    * fp;
  uint64_t* shape;
  nelem_t i;
  uint16_t * data;
  uint64_t  nelem;
  uint16_t   array_max;
  uint8_t format = 2;

  fp           = fopen(filename, "wb");
  if(!fp){
    // at_error_set(error,"[write_pgm] Can't open file for writing");
    return;
  }
  data         = a->d;
  shape        = a->h.shape;
  nelem        = a->h.n;
  array_max    = au16_max(a);

  fprintf(fp,  "P%d\n", format);
  fprintf(fp,"%d %d\n", (int)shape[1], (int)shape[0]);
  fprintf(fp,   "%d\n", array_max);
  if(format == 2) {
    for(i = 0; i < a->h.n; i++) {
      fprintf(fp,  "%d ", a->d[i]);
    }
  } else {
    fwrite(data, a->h.bitsize, nelem, fp);
  }

  fclose(fp);
}

