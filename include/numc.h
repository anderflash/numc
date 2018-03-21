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

#ifndef NUMC_H
#define NUMC_H

#include <stdint.h>

typedef uint64_t nelem_t;
#define REND UINT64_MAX

#include <stdint.h>
#ifndef NULL
#  ifdef __cplusplus
#  define NULL        (0L)
#  else /* !__cplusplus */
#  define NULL        ((void*) 0)
#  endif /* !__cplusplus */
#endif

#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	TRUE
#define	TRUE	(!FALSE)
#endif

#undef	MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef	MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))


typedef struct au8 {
  nelem_t* shape; /*!< Number of elements for each dimension */
  nelem_t* step; /*!< Number of elements between consecutive axis values */
  nelem_t* ostep; /*!< step for original matrix */
  uint8_t* d; /*!< Data array */
  nelem_t n; /*!< Number of elements */
  uint8_t dim; /*!< Number of dimensions */
  uint8_t owns;/*!< Does the array own the data? */
  nelem_t start;/*!< Slice (start > 0) or original (start = 0)? */
} au8;

/**
 * @brief Calculate step from a given shape
 * @param dim
 * @param step
 * @param shape
 */
void
step_from_shape(uint8_t dim, nelem_t *step, nelem_t *shape);

/**
 * @brief get_offset
 * @param dim
 * @param step
 * @param pos
 * @return
 */
nelem_t
get_offset(uint8_t dim, nelem_t *step, nelem_t* pos);

/**
 * @brief Create an array for 8-bit unsigned int values
 * @return the array
 */
au8*
au8_new();

/**
 * @brief Create a 8-bit unsigned int array with dimensions
 * @param dim
 * @return
 */
au8*
au8_new_dim(uint8_t dim);

/**
 * @brief Create a 8-bit unsigned int array with dimensions and shape
 * @param dim
 * @param shape
 * @return
 */
au8*
au8_new_shape(uint8_t dim, nelem_t *shape);

/**
 * @brief Create a 8-bit unsigned int array with dimensions and shape equal
 *        to another array
 * @param a
 * @return
 */
au8*
au8_new_like(au8* a);

/**
 * @brief Create a 8-bit unsigned int array with dimensions, shape and input data
 * @param dim
 * @param shape
 * @param data
 * @return
 */
au8*
au8_new_data(uint8_t dim, nelem_t* shape, uint8_t* data);

/**
 * @brief Create a 1D 8-bit unsigned int array with length
 * @param x
 * @return
 */
au8*
au8_new_1d(nelem_t x);

au8*
au8_new_1d_data(nelem_t x, uint8_t* d);

au8*
au8_new_2d(nelem_t x, nelem_t y);

au8*
au8_new_2d_data(nelem_t x, nelem_t y, uint8_t* d);

au8*
au8_new_3d(nelem_t x, nelem_t y, nelem_t z);

au8*
au8_new_3d_data(nelem_t x, nelem_t y, nelem_t z, uint8_t* d);

au8*
au8_new_4d(nelem_t x, nelem_t y, nelem_t z, nelem_t w);

au8*
au8_new_4d_data(nelem_t x, nelem_t y, nelem_t z, nelem_t w, uint8_t* d);

au8*
au8_zeros(uint8_t dim, nelem_t* shape);

au8*
au8_zeros_like(au8* a);

au8*
au8_ones(uint8_t dim, nelem_t* shape);

au8*
au8_ones_like(au8* a);

au8*
au8_eye(nelem_t rows);

au8*
au8_eye_cols(nelem_t rows, nelem_t cols);

au8*
au8_filled(uint8_t dim, nelem_t* shape, uint8_t value);

au8*
au8_filled_like(au8* a, uint8_t value);

nelem_t
au8_get_offset(au8 *a, nelem_t *pos);

uint8_t
au8_get_elem(au8 *a, nelem_t *pos);

uint8_t
au8_get_elem_offset(au8* a, nelem_t i);

au8*
au8_get(au8* a, uint8_t nranges, nelem_t* ranges);

/**
 * @brief Create a 1D 8-bit unsigned int array with length
 * @param x
 * @return
 */
void
au8_set(au8* a, uint8_t* d);

void
au8_set_elem(au8* a, nelem_t* pos, uint8_t value);

au8*
au8_add(au8 *a, au8 *b);

uint32_t
au8_dot(au8* a, au8* b);

void
au8_destroy(au8 *a);

#endif
