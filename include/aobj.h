#ifndef AOBJ_H
#define AOBJ_H

#include <aheader.h>
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
