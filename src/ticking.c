/*
 * Define the functions that allow for playing of the tick
 */

#include "ticking.h"

const char audio[] = "/ca/awisse/ticker/audio/clicker-low.ogg";

void
rewind_stream (GtkMediaStream *stream,
               gpointer       user_data)
{
  g_print("Timestamp after: %ld\n", gtk_media_stream_get_timestamp (stream));
  gtk_media_stream_seek (stream, 0);
}

guint
play_tick (gpointer user_data)
{
  static GtkMediaStream* stream = NULL;

  g_print("GtkMediaStream: %p\n", stream);

  if (!stream) {
    stream = gtk_media_file_new_for_resource (audio);
    gtk_media_stream_set_volume (stream, 1.0);
    g_signal_connect (stream, "notify::ended", G_CALLBACK (rewind_stream), NULL);
  }

  g_print("Timestamp before: %ld\n", gtk_media_stream_get_timestamp (stream));

  gtk_media_stream_play (stream);

  return TRUE;
}


