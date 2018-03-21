#ifndef UTIL_H
#define UTIL_H
#include <stdint.h>
#include "type.h"
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

#endif
