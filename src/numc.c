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
  return a;
}

au8*
au8_new_like(au8* a) {
  return au8_new_shape(a->dim, a->shape);
}

au8*
au8_new_1D(nelem_t x) {
  return au8_new_shape(1, &x);
}

void
au8_set(au8* a, uint8_t* d) {
  memcpy(a->d,d,sizeof(uint8_t) * a->n);
}

au8*
au8_new_1D_d(nelem_t x, uint8_t* d) {
  au8* a = au8_new_1D(x);
  au8_set(a, d);
  return a;
}

uint32_t
au8_dot(au8* a, au8* b) {
  uint64_t i;
  uint32_t c = 0;

  for(i = 0; i < a->n; i++) c += a->d[i] * b->d[i];
  return c;
}

au8*
au8_new_2D(nelem_t x, nelem_t y) {
  nelem_t shape[] = {x,y};
  return au8_new_shape(2, shape);
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
  free(a->d);
  free(a);
}

//void
//multiply (A, x) {
//  b = 0;
//  for (i = 0; i < m; i++) {
//    for(j = 0; j )
//  }
//}
