#include <numc.h>
#include <stdlib.h>
#include <string.h>

au8*
au8_new() {
  au8* a = calloc(1, sizeof(au8));
  return a;
}

au8*
au8_new_dim(uint8_t dim) {
  au8* a = au8_new();
  a->dim = dim;
  a->shape = malloc(sizeof(uint64_t) * dim);
  return a;
}

au8*
au8_new_shape(uint8_t dim, nelem_t* shape) {
  au8* a = au8_new_dim(dim);
  uint64_t n = 1;
  uint8_t i;
  memcpy(a->shape, shape, dim * sizeof(uint64_t));
  for(i = 0; i < a->dim; i++) n *= a->shape[i];
  a->d = malloc(sizeof(uint8_t) * n);
  a->n = n;
  a->owns = TRUE;
  return a;
}

au8*
au8_new_like(au8* a) {
  return au8_new_shape(a->dim, a->shape);
}

au8*
au8_new_data(uint8_t dim, nelem_t* shape, uint8_t* data) {
  au8* a = au8_new();
  size_t shapebyte = sizeof(nelem_t) * dim;
  nelem_t n = 1;
  uint8_t i;
  a->dim = dim;
  a->shape = malloc(shapebyte);
  memcpy(a->shape, shape, shapebyte);
  for(i = 0; i < dim; i++) n *= shape[i];
  a->n = n;
  a->d = data;
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

void
au8_set(au8* a, uint8_t* d) {
  memcpy(a->d,d,sizeof(uint8_t) * a->n);
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
