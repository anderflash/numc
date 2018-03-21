#ifndef AHEADER_H
#define AHEADER_H
#include <stdint.h>
#include "type.h"

#define REND UINT64_MAX

typedef struct aheader {
  nelem_t* shape; /*!< Number of elements for each dimension */
  nelem_t* step; /*!< Number of elements between consecutive axis values */
  nelem_t* ostep; /*!< step for original matrix */
  nelem_t n; /*!< Number of elements */
  nelem_t start;/*!< Slice (start > 0) or original (start = 0)? */
  uint8_t dim; /*!< Number of dimensions */
  uint8_t owns;/*!< Does the array own the data? */
  uint8_t bitsize;/*!< Does the array own the data? */
} aheader;

#endif
