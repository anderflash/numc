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
au8_eye(uint8_t rows) {
  return au8_eye_cols(rows, rows);
}

au8*
au8_eye_cols(uint8_t rows, uint8_t cols) {
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
