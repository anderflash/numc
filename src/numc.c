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

//void
//multiply (A, x) {
//  b = 0;
//  for (i = 0; i < m; i++) {
//    for(j = 0; j )
//  }
//}
