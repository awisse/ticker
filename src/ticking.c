/*
 * Define the functions that allow for playing of the tick
 */

#include "ticking.h"

const char audio[] = "/ca/awisse/ticker/audio/clicker-low.ogg";

guint
play_tick (gpointer user_data)
{
  GtkMediaStream* stream = NULL;

  stream = gtk_media_file_new_for_resource (audio);

  gtk_media_stream_set_volume (stream, 1.0);

  /* Delete after
  g_signal_connect (stream, "notify::ended", G_CALLBACK (g_object_unref), NULL);

  gtk_media_stream_play (stream);

  return TRUE;
}
