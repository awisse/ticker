/*
 * Header for tick playing
 */
#pragma once

#include <gtk/gtk.h>

typedef struct _ticker {
  gint counter;
  gint64 first_tick;

} ticker;

gint
start_ticking (void);

void
stop_ticking (void);

gboolean
update_tick (void* user_data);

gint
get_seconds (void);
