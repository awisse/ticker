/*
 * Define the functions that allow for playing of the tick
 */

#include "ticking.h"

const char audio[] = "/ca/awisse/ticker/audio/clicker-low.ogg";
ticker* timer;

void
play_tick(void);

gint
start_ticking (void) {

  if (!timer) {
    timer = (ticker*) g_malloc (sizeof (timer));
  }

  if (timer) {
    timer->counter = 1;
    timer->first_tick = g_get_monotonic_time ();
    return 0;
  }

  // Couldn't allocate memory above.
  return -1;
}

void stop_ticking (void) {
  g_free (timer);
  timer = NULL;
}

gboolean
update_tick (void* user_data)
{
  gint64 now, elapsed;

  now = g_get_monotonic_time ();
  elapsed =  now - timer->first_tick;

  if (elapsed > (timer->counter) * 1000000) {
    /* First the sound */
    play_tick();

    /* Advance counter to presently elapsed in case computer was sleeping */
    timer->counter = elapsed / 1000000 + 1;
  }
  return G_SOURCE_CONTINUE;
}

void
play_tick (void)
{
  GtkMediaStream* stream;

  stream = gtk_media_file_new_for_resource (audio);
  gtk_media_stream_set_volume (stream, 1.0);
  g_signal_connect (stream, "notify::ended", G_CALLBACK (g_object_unref), NULL);

  gtk_media_stream_play (stream);
}

gint
get_seconds (void)
{
  return timer->counter;
}






