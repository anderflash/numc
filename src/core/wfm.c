#include <nc/core.h>
#include <stdlib.h>
#include <string.h>

static void
wfm_read_header(void* h, FILE* ifp, size_t objsize) {
  char* buffer;
  int size = 0;
  fread(&size, 1, sizeof(size), ifp);
  buffer = (char*) malloc(size);
  if (buffer) {
    fseek(ifp, - (int)(sizeof(size)), SEEK_CUR);
    fread(buffer, 1, size, ifp);
    memcpy(h, buffer, objsize);
    free(buffer);
  }
}
static void
wfm_read_waveform_header(wfmwh *h, FILE* ifp) {
  wfm_read_header(h, ifp, sizeof(wfmwh));
  if (h->type > WFM_LOGIC)
    h->type = WFM_UNKNOWN;
}
static void
wfm_read_data_header(wfmdh *h, FILE* ifp) {
  wfm_read_header(h, ifp, sizeof(wfmdh));
  if (h->type > WFM_DATA_LOGIC)
    h->type = WFM_DATA_UNKNOWN;
}

static void*
wfm_read_data(wfmwh *h, FILE *ifp, wfmdatatype* bufferType, wfmdatatype* validtypes, uint8_t nvalidtypes, uint8_t bytesperpoint) {
  wfmdh dh;
  void* d;
  wfm_read_data_header(&dh, ifp);
  int n = dh.buffersize / dh.bytesperpoint;
  uint8_t typeValid = FALSE, i;
  for(i = 0; i < nvalidtypes; i++) if(dh.type == validtypes[i]) {typeValid = TRUE; break;}
  if(dh.bytesperpoint == bytesperpoint && typeValid && n == h->points)
    if (d = malloc(dh.buffersize)) fread(d, 1, dh.buffersize, ifp);
  if (d == NULL) {
    fseek(ifp, dh.buffersize, SEEK_CUR);
    if (bufferType != NULL) *bufferType = WFM_DATA_UNKNOWN;
  }
  return d;
}

static float*
wfm_read_analog(wfmwh *wh, FILE* ifp, wfmdatatype* bufferType) {
  wfmdatatype validTypes[] = {WFM_DATA_NORMAL,WFM_DATA_MIN, WFM_DATA_MAX};
  return wfm_read_data(wh, ifp, bufferType, validTypes, 3, 4);
}

static void
wfm_read_normal(wfmnormal* w, FILE* ifp) {
  w->data = wfm_read_analog(&w->header, ifp, NULL);
}

static void
wfm_read_peak(wfmpeak* w, FILE* ifp) {
  float *mind, *maxd, *tmpd;
  wfmdatatype bufferType;
  mind = wfm_read_analog(&w->header, ifp, &bufferType);
  maxd = wfm_read_analog(&w->header, ifp, &bufferType);
  if(bufferType == WFM_DATA_MAX) { tmpd = mind; mind = maxd; maxd = tmpd; }
  w->min = mind;  w->max = maxd;
}

static void
wfm_read_hist(wfmhist* w, FILE* ifp) {
  wfmdatatype validTypes[] = {WFM_DATA_COUNTS};
  w->data = wfm_read_data(&w->header, ifp, NULL, validTypes, 1, 4);
}

static void
wfm_read_logic(wfmlogic* w, FILE* ifp) {
  wfmdatatype validTypes[] = {WFM_DATA_LOGIC};
  uint8_t i;
  for(i == 0; i < w->header.nbuffers; i++)
    w->data[i] = wfm_read_data(&w->header, ifp, NULL, validTypes, 1, 1);
}

static void
wfm_ignore_waveform(FILE* ifp)
{
  wfmdh h;
  wfm_read_data_header(&h, ifp);
  fseek(ifp, h.buffersize, SEEK_CUR);
}

static void
wfm_read_waveform(wfmw* ww, FILE* ifp) {
  wfm_read_waveform_header(&ww->header, ifp);
  uint8_t i;
  switch(ww->header.type)
  {
    case WFM_NORMAL:
    case WFM_AVERAGE:
      wfm_read_normal((wfmnormal*) ww, ifp);
      break;
    case WFM_PEAK_DETECT:
      wfm_read_peak((wfmpeak*) ww, ifp);
      break;
    case WFM_HORZ_HISTOGRAM:
    case WFM_VERT_HISTOGRAM:
      wfm_read_hist((wfmhist*) ww, ifp);
      break;
    case WFM_LOGIC:
      wfm_read_logic((wfmlogic*) ww, ifp);
      break;
    default:
    case WFM_UNKNOWN:
      for(i = 0; i < ww->header.nbuffers; ++i)
        wfm_ignore_waveform(ifp);
      break;
  }
}

wfm *
wfm_read(char* filename) {
  wfm* w = malloc(sizeof(wfm));
  FILE* ifp = fopen(filename, "rb");
  if (ifp) {
    fread(w, 1, sizeof(w->header), ifp);
    if (w->header.cookie[0] == 'A' && w->header.cookie[1] == 'G') {
      int i;
      w->waveforms = malloc(sizeof(wfmw) * w->header.n);
      for (i = 0; i < w->header.n; ++i)
        wfm_read_waveform(&w->waveforms[i], ifp);
    }
  }
  fclose(ifp);
  return w;
}

void
wfm_destroy(wfm* w) {
  uint8_t i;
  if(w) {
    if(w->waveforms) {
      for (i = 0; i < w->header.n; ++i) {
        switch (w->waveforms[i].header.type) {
        case WFM_NORMAL:
          free(((wfmnormal*)&w->waveforms[i])->data);
          break;
        default:
          break;
        }
      }
      free(w->waveforms);
    }
    free(w);
  }
}
