#pragma once

#include <pico/types.h>

#define EVENT_BUF_SIZE 200

typedef enum EvType {
  GO_0, // Play motor with index "GO_<index>"
  GO_1,
  GO_2,
  GO_3,
  GO_4,
  GO_5,
  GO_6,
  GO_7,
  GO_8,
  GO_9,
  GO_10,
  GO_11,
  END_GLYPH, // Denote the end of a glyph
} EvType;

typedef struct Ev {
  absolute_time_t abs_time;
  EvType ev_type;
} Ev;

typedef struct EvBuf {
  Ev* buffer;
  int head;
  int tail;
} EvBuf;

EvBuf ev_buf();

void eb_free(EvBuf ev_buf);

bool eb_is_empty(EvBuf *eb);

int eb_queue(EvBuf *eb, Ev event, absolute_time_t offset);

int eb_queue_mult(EvBuf *eb, Ev event, absolute_time_t offset, float mult);

Ev eb_pop(EvBuf *eb);

Ev eb_peek(EvBuf *eb);

absolute_time_t eb_last_timestamp(EvBuf *eb);
