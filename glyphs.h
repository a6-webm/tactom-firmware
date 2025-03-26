#include "event.h"

#define MS(us) (us * 1000)

void queue_event(EvBuf *eb, Ev event, absolute_time_t offset);

void queue_glyph_events(EvBuf *eb, char c);
