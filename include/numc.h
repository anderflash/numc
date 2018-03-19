#ifndef NUMC_H
#define NUMC_H

#include <stdint.h>

typedef uint64_t nelem_t;

#include <stdint.h>
#ifndef NULL
#  ifdef __cplusplus
#  define NULL        (0L)
#  else /* !__cplusplus */
#  define NULL        ((void*) 0)
#  endif /* !__cplusplus */
#endif

typedef struct au8 {
  nelem_t* shape; /*!< Number of elements for each dimension */
  uint8_t* d; /*!< Data array */
  nelem_t n; /*!< Number of elements */
  uint8_t dim; /*!< Number of dimensions */
} au8;

/**
 * Create an array for 8-bit unsigned int values
 * @brief Create an array for 8-bit unsigned int values
 * @return the array
 */
au8*
au8_new();

au8*
au8_new_dim(uint8_t dim);

au8*
au8_new_shape(uint8_t dim, nelem_t *shape);

au8*
au8_new_like(au8* a);

au8*
au8_new_1D(nelem_t x);

void
au8_set(au8* a, uint8_t* d);

au8*
au8_new_1D_d(nelem_t x, uint8_t* d);

au8*
au8_new_2D(nelem_t x, nelem_t y);

au8*
au8_zeros(uint8_t dim, nelem_t* shape);

au8*
au8_zeros_like(au8* a);

au8*
au8_ones(uint8_t dim, nelem_t* shape);

au8*
au8_ones_like(au8* a);

au8*
au8_add(au8 *a, au8 *b);

uint32_t
au8_dot(au8* a, au8* b);

void
au8_destroy(au8 *a);

#endif
