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

#ifndef NC_CORE_WFM_H
#define NC_CORE_WFM_H

#include <stdio.h>
#include <stdint.h>
#define DATE_TIME_STRING_LENGTH 16
#define FRAME_STRING_LENGTH 24
#define SIGNAL_STRING_LENGTH 16

#define WFM_TIMESTAMP(i, h) (((double) i * h.xincrement) + h.xorigin)

// #define WFM_TIMESTAMP(i, h) _Generic((h),
//  wfmw*: (((double) i * h.header.xincrement) + h.header.xorigin),
//  wfmwh: (((double) i * h.xincrement) + h.xorigin))(h);

typedef struct {char cookie[2]; char version[2]; int size; int n;} wfmh;
typedef struct {
   int size;
   int type;
   int nbuffers;
   int points;
   int count;
   float xdisplayrange;
   double xdisplayorigin;
   double xincrement;
   double xorigin;
   int xunits;
   int yunits;
   char date[DATE_TIME_STRING_LENGTH];
   char time[DATE_TIME_STRING_LENGTH];
   char frame[FRAME_STRING_LENGTH];
   char label[SIGNAL_STRING_LENGTH];
   double timetag;
   unsigned int segmentindex;
} wfmwh;
typedef struct {wfmwh header; uint8_t padding[16];    } wfmw;
typedef struct {wfmh header; wfmw *waveforms;} wfm;

typedef struct {wfmwh header; float* data;            } wfmnormal;
typedef struct {wfmwh header; float* min;  float* max;} wfmpeak;
typedef struct {wfmwh header; int* data;              } wfmhist;
typedef struct {wfmwh header; uint8_t* data[2];       } wfmlogic;

typedef struct {int size; short type; short bytesperpoint; int buffersize;} wfmdh;

typedef enum {
   WFM_UNKNOWN,
   WFM_NORMAL,
   WFM_PEAK_DETECT,
   WFM_AVERAGE,
   WFM_HORZ_HISTOGRAM,
   WFM_VERT_HISTOGRAM,
   WFM_LOGIC
} wfmwtype;

typedef enum {
   WFM_DATA_UNKNOWN,
   WFM_DATA_NORMAL,
   WFM_DATA_MAX,
   WFM_DATA_MIN,
   WFM_DATA_TIME,
   WFM_DATA_COUNTS,
   WFM_DATA_LOGIC
} wfmdatatype;

wfm*
wfm_read(char* filename);
void
wfm_destroy(wfm* w);
#endif
