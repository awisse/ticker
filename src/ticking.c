/*
 * Define the functions that allow for playing of the tick
 */

#include "ticking.h"

const char audio[] = "/ca/awisse/ticker/audio/service-login.oga";

static void
sound_notified (GtkMediaStream* stream,
                gpointer data)
{
  g_print("has-audio: %d\n", gtk_media_stream_has_audio (stream));
}

static void
sound_timestamp (gpointer data)
{
  GtkMediaStream* stream = GTK_MEDIA_STREAM (data);
  g_print ("Timestamp: %ld\n", gtk_media_stream_get_timestamp (stream));
}

static void
sound_ended (GtkMediaStream *stream,
             gpointer        data)
{
  g_print ("Sound ended\n");
  g_object_unref (stream);
}

void play_tick(void)
{
  GtkMediaStream* stream = NULL;
  guint timeout_id;

  stream = gtk_media_file_new_for_resource (audio);
  g_signal_connect (stream, "notify::prepared", G_CALLBACK (sound_notified), NULL);

  gtk_media_stream_set_volume (stream, 1.0);

  g_signal_connect (stream, "notify::ended", G_CALLBACK (sound_ended), NULL);

  gtk_media_stream_play (stream);

  timeout_id = g_timeout_add_once (100, sound_timestamp, stream);

  g_print ("TimeoutID: %u\n", timeout_id);
  g_print ("Playing  : %d\n", gtk_media_stream_get_playing (stream));

}
