#include "event.h"
#include <pico/time.h>
#include <stdlib.h>

EvBuf ev_buf() {
  EvBuf ev_buf;
  ev_buf.buffer = malloc(EVENT_BUF_SIZE * sizeof(Ev));
  ev_buf.head = 0;
  ev_buf.tail = 0;
  return ev_buf;
}

void eb_free(EvBuf ev_buf) { free(ev_buf.buffer); }

int inc1(int x) { return x + 1 == EVENT_BUF_SIZE ? 0 : x + 1; }
int dec1(int x) { return x == 0 ? EVENT_BUF_SIZE - 1 : x - 1; }

bool eb_is_empty(EvBuf *eb) { return eb->head == eb->tail; }

bool eb_is_full(EvBuf *eb) { return inc1(eb->head) == eb->tail; }

int eb_queue(EvBuf *eb, Ev event, absolute_time_t offset) {
  if (eb_is_full(eb))
    return -1;
  event.abs_time += offset;
  eb->buffer[eb->head] = event;
  eb->head = inc1(eb->head);
  return 0;
}

int eb_queue_mult(EvBuf *eb, Ev event, absolute_time_t offset, float mult) {
  event.abs_time *= mult;
  return eb_queue(eb, event, offset);
}

Ev eb_pop(EvBuf *eb) {
  Ev event = eb->buffer[eb->tail];
  if (eb_is_empty(eb))
    return event; // Silently errors
  eb->tail = inc1(eb->tail);
  return event;
}

Ev eb_peek(EvBuf *eb) {
  Ev event = eb->buffer[eb->tail];
  return event; // Silently errors if buffer is empty
}

absolute_time_t eb_last_timestamp(EvBuf *eb) {
  if (eb_is_empty(eb))
    return get_absolute_time();
  int idx = dec1(eb->head);
  return eb->buffer[idx].abs_time;
}
