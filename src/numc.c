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

#include <numc.h>
#include <stdlib.h>
#include <string.h>

void
step_from_shape(uint8_t dim, nelem_t *step, nelem_t *shape) {
  uint8_t i;
  step[dim-1] = 1;
  for(i = dim-1; i > 0; i--) step[i-1] = step[i] * shape[i];
}

nelem_t
get_offset(uint8_t dim, nelem_t *step, nelem_t* pos) {
  nelem_t offset = 0;
  uint8_t i;
  for(i = 0; i < dim; i++) offset += pos[i] * step[i];
  return offset;
}

au8*
au8_new() {
  au8* a = calloc(1, sizeof(au8));
  a->bitsize = 1;
  return a;
}

au8*
au8_new_dim(uint8_t dim) {
  au8* a = au8_new();
  a->dim = dim;
  a->shape = malloc(sizeof(nelem_t) * (dim << 3));
  a->ostep = a->shape + dim;
  a->step = a->ostep + dim;
  return a;
}

static au8*
au8_new_shape_core(uint8_t dim, nelem_t* shape) {
  au8* a = au8_new_dim(dim);
  nelem_t n = 1;
  uint8_t i;
  memcpy(a->shape, shape, sizeof(nelem_t) * dim);
  a->step[dim-1] = 1;
  for(i = 0; i < dim; i++) n *= shape[i];
  for(i = dim-1; i > 0; i--) a->step[i-1] = a->step[i] * a->shape[i];
  memcpy(a->ostep, a->step, sizeof(nelem_t) * dim);
  a->n = n;
}

au8*
au8_new_shape(uint8_t dim, nelem_t* shape) {
  au8* a = au8_new_shape_core(dim, shape);
  a->d = malloc(sizeof(uint8_t) * a->n);
  a->owns = TRUE;
  return a;
}

au8*
au8_new_like(au8* a) {
  return au8_new_shape(a->dim, a->shape);
}

au8*
au8_new_data(uint8_t dim, nelem_t* shape, uint8_t* data) {
  au8* a = au8_new_shape_core(dim, shape);
  a->d = data;
  a->owns = FALSE;
  return a;
}

au8*
au8_new_1d(nelem_t x) {
  return au8_new_shape(1, &x);
}

au8*
au8_new_1d_data(nelem_t x, uint8_t* d) {
  au8* a = au8_new_data(1, &x, d);
  return a;
}

au8*
au8_new_2d(nelem_t x, nelem_t y){
  nelem_t shape[] = {x,y};
  return au8_new_shape(2, shape);
}

au8*
au8_new_2d_data(nelem_t x, nelem_t y, uint8_t *d) {
  nelem_t shape[] = {x,y};
  au8* a = au8_new_data(2, shape, d);
  return a;
}

au8*
au8_new_3d(nelem_t x, nelem_t y, nelem_t z) {
  nelem_t shape[] = {x,y,z};
  return au8_new_shape(3, shape);
}

au8*
au8_new_3d_data(nelem_t x, nelem_t y, nelem_t z, uint8_t *d) {
  nelem_t shape[] = {x,y,z};
  au8* a = au8_new_data(3, shape, d);
  return a;
}

au8*
au8_new_4d(nelem_t x, nelem_t y, nelem_t z, nelem_t w) {
  nelem_t shape[] = {x,y,z,w};
  return au8_new_shape(4, shape);
}

au8*
au8_new_4d_data(nelem_t x, nelem_t y, nelem_t z, nelem_t w, uint8_t *d) {
  nelem_t shape[] = {x,y,z,w};
  au8* a = au8_new_data(4, shape, d);
  return a;
}

nelem_t
au8_get_offset(au8 *a, nelem_t *pos) {
  return get_offset(a->dim, a->step, pos);
}

uint8_t
au8_get_elem(au8 *a, nelem_t* pos) {
  return a->d[au8_get_offset(a, pos)];
}

au8*
au8_get(au8* a, uint8_t nranges, nelem_t* ranges) {
  // Get array with same dimension as a
  au8* b = au8_new_dim(a->dim);
  nelem_t start = 0; // index of initial element
  nelem_t n = 1;
  uint8_t i, i2; // iterators for range (i and 2*i)
  // Same original step
  memcpy(b->ostep, a->ostep, a->dim * sizeof(nelem_t));
  // Same data
  b->d = a->d;

  // Calculate start
  for(i = 0; i < nranges ; i++) {
    i2 = i << 1;
    start += ranges[i2] * a->step[i];
    // Calculate new shape
    b->shape[i] = MIN(ranges[i2+1], a->shape[i]) - ranges[i2];
    // Number of elements
    n *= b->shape[i];
  }
  for(; i < b->dim; i++) {
    b->shape[i] = a->shape[i];
    n *= b->shape[i];
  }
  b->start = start;
  b->n = n;

  // Step size
  step_from_shape(b->dim, b->step, b->shape);
  return b;
}

uint8_t
au8_get_elem_offset(au8* a, nelem_t i) {
  // Convert 1D into ND pos based on slice step
  nelem_t* pos = malloc(sizeof(nelem_t) * a->dim);
  uint8_t k;
  for(k = 0; k < a->dim; k++) {
    pos[k] = i / a->step[k];
    i %= a->step[k];
  }
  i = a->start;

  // Convert ND into 1D based on original step
  for(k = 0; k < a->dim; k++) {
    i += pos[k] * a->ostep[k];
  }
  return a->d[i];
}

void
au8_set(au8* a, uint8_t* d) {
  memcpy(a->d,d,sizeof(uint8_t) * a->n);
}

void
au8_set_elem(au8* a, nelem_t *pos, uint8_t value) {
  nelem_t offset = 0;
  uint8_t i;
  for(i = 0; i < a->dim; i++) offset += pos[i] * a->step[i];
  a->d[offset] = value;
}

uint32_t
au8_dot(au8* a, au8* b) {
  uint64_t i;
  uint32_t c = 0;

  for(i = 0; i < a->n; i++) c += a->d[i] * b->d[i];
  return c;
}

au8*
au8_zeros(uint8_t dim, nelem_t* shape) {
  au8* a = au8_new_shape(dim, shape);
  memset(a->d, 0, sizeof(uint8_t) * a->n);
  return a;
}

au8*
au8_zeros_like(au8* a) {
  return au8_zeros(a->dim, a->shape);
}

au8*
au8_ones(uint8_t dim, nelem_t* shape) {
  uint64_t i;
  au8* a = au8_new_shape(dim, shape);
  for(i = 0; i < a->n; i++){
    a->d[i] = 1;
  }
  return a;
}

au8*
au8_ones_like(au8* a) {
  return au8_ones(a->dim, a->shape);
}

au8*
au8_eye(nelem_t rows) {
  return au8_eye_cols(rows, rows);
}

au8*
au8_eye_cols(nelem_t rows, nelem_t cols) {
  nelem_t shape[] = {rows, cols};
  au8* a = au8_zeros(2, shape);
  nelem_t step = a->step[0] + a->step[1];
  uint8_t i;
  for(i = 0; i < a->n; i += step) {
    a->d[i] = 1;
  }
  return a;
}

au8*
au8_filled(uint8_t dim, nelem_t* shape, uint8_t value) {
  au8* a = au8_new_shape(dim, shape);
  memset(a->d, value, a->n * sizeof(dim));
  return a;
}

au8*
au8_filled_like(au8* a, uint8_t value) {
  return au8_filled(a->dim, a->shape, value);
}

au8*
au8_copy(au8* a) {
  au8* b = au8_new_like(a);
  au8_set(b, a->d);
  return b;
}

void
au8_save_gzip(char* filename, uint8_t narrays, char** names, au8** arrays) {

  ncz* fp = ncz_open(filename, "wb", TRUE);
  uint8_t i,len;

  // write number of arrays
  ncz_write(fp,&narrays,sizeof(uint8_t),1);

  // write names
  for(i = 0; i < narrays; i++){
    len = strlen(names[i]);
    ncz_write(fp,&len,sizeof(uint8_t),1);
    ncz_write(fp,names[i],sizeof(char),len);
  }

  // write proper arrays
  for(i = 0; i < narrays; i++){
    // write n, start, dim, owns_data and elemsize
    ncz_write(fp,&arrays[i]->n, (sizeof(nelem_t) << 1) + (sizeof(uint8_t) << 1) + sizeof(uint8_t), 1);

    // write shape and step
    ncz_write(fp,arrays[i]->shape, sizeof(nelem_t), arrays[i]->dim);
    ncz_write(fp,arrays[i]->step, sizeof(nelem_t), arrays[i]->dim);

    // write data
    ncz_write(fp,arrays[i]->d, arrays[i]->bitsize, arrays[i]->n);
  }

  // close the file
  ncz_close(fp);
}

au8*
au8_load_gzip(char* filename, uint8_t* narraysp, char*** namesp) {
  char            ** names;
  au8              * ar;
  ncz              * fp;
  uint8_t            i;
  uint8_t            len;
  uint8_t            num;

  // open the file
  fp = ncz_open(filename, "rb", TRUE);

  // read number of arrays
  ncz_read(fp, narraysp, sizeof(uint8_t), 1);
  num = *narraysp;

  // read names
  *namesp =(char**) malloc(num*sizeof(char*));
  names = *namesp;
  for(i = 0; i < num; i++){
    // Read length of each name
    ncz_read(fp,&len,sizeof(uint8_t),1);
    names[i] = (char*)malloc(sizeof(char)*(len+1));
    ncz_read(fp,names[i],sizeof(char),len);
    names[i][len] = '\0';
  }

  // read proper arrays
  ar = malloc(sizeof(au8)*num);
  for(i = 0; i < num; i++){
    // read nelem, dim, owns_data and elemsize
    ncz_read(fp, &ar[i].n, (sizeof(nelem_t) << 1) + (sizeof(uint8_t) << 1) + sizeof(uint8_t),1);

    // read shape and step
    ar[i].shape = malloc(sizeof(nelem_t)* ar[i].dim);
    ar[i].step  = malloc(sizeof(nelem_t)* ar[i].dim);
    ar[i].ostep  = malloc(sizeof(nelem_t)* ar[i].dim);
    ncz_read(fp,ar[i].shape,sizeof(nelem_t),ar[i].dim);
    ncz_read(fp,ar[i].step ,sizeof(nelem_t),ar[i].dim);
    memcpy(ar[i].ostep, ar[i].step, sizeof(nelem_t)*ar[i].dim);

    // read data
    ar[i].d = malloc(ar[i].bitsize * ar[i].n);
    ncz_read(fp, ar[i].d, ar[i].bitsize, ar[i].n);
  }

  // close the file
  ncz_close(fp);
  return ar;
}

au8*
au8_add(au8 *a, au8 *b) {
  au8* c = au8_new_like(a);
  return NULL;
}

void
au8_destroy(au8 *a) {
  free(a->shape);
  if(a->owns) free(a->d);
  free(a);
}

//void
//multiply (A, x) {
//  b = 0;
//  for (i = 0; i < m; i++) {
//    for(j = 0; j )
//  }
//}
