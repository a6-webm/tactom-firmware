#include <pico/types.h>

#define EVENT_BUF_SIZE 100

typedef enum EvType {
  DRV_0, // Play effect on drive "DRV_<index>"
  DRV_1,
  DRV_2,
  DRV_3,
  DRV_4,
  DRV_5,
  DRV_6,
  DRV_7,
  DRV_8,
  DRV_9,
  DRV_10,
  DRV_11,
  END_GLYPH, // Denote the end of a glyph
} EvType;

typedef struct Ev {
  absolute_time_t abs_time;
  EvType ev_type;
} Ev;

typedef struct EvBuf {
  Ev buffer[EVENT_BUF_SIZE];
  int head;
  int tail;
  int count;
} EvBuf;

inline bool eb_is_empty(EvBuf *eb);

int eb_queue(EvBuf *eb, Ev event, absolute_time_t offset);

Ev eb_pop(EvBuf *eb);

absolute_time_t eb_last_timestamp(EvBuf *eb);
