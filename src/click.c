/*
 * Define the functions that allow for playing of the tick
 */

#include "config.h"
#include "click.h"

const char audio[] = RESOURCE_BASE_PATH "/audio/clicker-low.ogg";

static void
play_click (void)
{
  GtkMediaStream* stream;

  stream = gtk_media_file_new_for_resource (audio);
  gtk_media_stream_set_volume (stream, 1.0);
  g_signal_connect (stream, "notify::ended", G_CALLBACK (g_object_unref), NULL);

  gtk_media_stream_play (stream);
}

void
click_cb (GObject  *object,
          gpointer  data)
{
  play_click();
}

