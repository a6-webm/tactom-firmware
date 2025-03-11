#include "event.h"
#include <pico/time.h>

inline bool eb_is_empty(EvBuf *eb) { return eb->count == 0; }

int eb_queue(EvBuf *eb, Ev event, absolute_time_t offset) {
  if (eb->count == EVENT_BUF_SIZE)
    return -1;
  event.abs_time += offset;
  eb->buffer[eb->head] = event;
  eb->head++;
  if (eb->head == EVENT_BUF_SIZE)
    eb->head = 0;
  eb->count++;
  return 0;
}

Ev eb_pop(EvBuf *eb) {
  Ev event = eb->buffer[eb->tail];
  if (eb->count == 0)
    return event; // Silently errors
  eb->tail++;
  if (eb->head == EVENT_BUF_SIZE)
    eb->head = 0;
  eb->count--;
  return event;
}

absolute_time_t eb_last_timestamp(EvBuf *eb) {
  if (eb->count == 0)
    return get_absolute_time();
  int idx = eb->head - 1;
  if (idx < 0)
    idx = EVENT_BUF_SIZE - 1;
  return eb->buffer[eb->head - 1].abs_time;
}
