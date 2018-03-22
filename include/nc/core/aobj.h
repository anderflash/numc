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

#ifndef NC_CORE_AOBJ_H
#define NC_CORE_AOBJ_H

#include <nc/core.h>
#include <stdint.h>
typedef struct au8 {
  aheader h;
  uint8_t *d;
} au8;
typedef struct au16 {
  aheader h;
  uint16_t *d;
} au16;
typedef struct au32 {
  aheader h;
  uint32_t *d;
} au32;
typedef struct au64 {
  aheader h;
  uint64_t *d;
} au64;
typedef struct ai8 {
  aheader h;
  int8_t *d;
} ai8;
typedef struct ai16 {
  aheader h;
  int16_t *d;
} ai16;
typedef struct ai32 {
  aheader h;
  int32_t *d;
} ai32;
typedef struct ai64 {
  aheader h;
  int64_t *d;
} ai64;
typedef struct af {
  aheader h;
  float *d;
} af;
typedef struct ad {
  aheader h;
  double *d;
} ad;

#endif
