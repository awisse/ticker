/*
 * Header for tick playing
 */
#pragma once

#include <gtk/gtk.h>

void
rewind_stream (GtkMediaStream *stream,
               gpointer       user_data);

guint
play_tick (gpointer user_data);

