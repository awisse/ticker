#define G_LOG_DOMAIN "ttimer-ttimer"
#include "ttimer.h"

static guint t_timer_signal;

struct _TTimer {
  GObject parent;
  GTimer* gtimer;
  guint counter;
  guint timeout_id;
  gboolean running;
};

G_DEFINE_TYPE (TTimer, t_timer, G_TYPE_OBJECT)

static void
seconds_updated_cb (TTimer *self) {
  g_info ("Seconds updated: %u", t_timer_get_seconds(self, NULL));
}

/* Return full seconds elapsed since the start of the timer */
guint
t_timer_get_seconds (TTimer *self, guint *seconds) {
  if (seconds) 
    *seconds = self->counter;
  return self->counter;
}

gboolean t_timer_check (TTimer *self);

void
t_timer_start (TTimer *self) {
  g_timer_start (self->gtimer);
  self->timeout_id = g_timeout_add (10, G_SOURCE_FUNC (t_timer_check), self);

  self->counter = 0;
  self->running = TRUE;
  g_debug ("TTimer started");
}

void
t_timer_stop (TTimer *self) {

  if (!self->running)
    return;

  /* This shouldn't happen: timeout_id == 0 **and** running */
  g_assert (self->timeout_id);

  if (!g_source_remove (self->timeout_id)) {
      g_warning ("Timeout source %u not found", self->timeout_id);
  }
  g_timer_stop (self->gtimer);
  self->running = FALSE;
  g_debug ("TTimer stopped");
}

void
t_timer_reset (TTimer *self) {
    g_timer_reset (self->gtimer);
}

/* Return microseconds elapsed since the start of the timer */
gdouble
t_timer_elapsed (TTimer *self) {
    gdouble elapsed;
    elapsed = g_timer_elapsed (self->gtimer, NULL);
    return elapsed;
}

gboolean
t_timer_check (TTimer *self) {

    gdouble elapsed = g_timer_elapsed (self->gtimer, NULL);

    if ((guint)elapsed > self->counter) {
        (self->counter)++;
        g_signal_emit (self, t_timer_signal, 0);
    }
    return G_SOURCE_CONTINUE;
}

void
t_timer_finalize (GObject *object)
{
  TTimer *timer = T_TIMER (object);

  /* Stop Timer first. Cleans up timeout source if running. */
  t_timer_stop (timer);

  /* Free GTimer memory */
  g_timer_destroy (timer->gtimer);
  g_debug ("TTimer->GTimer destroyed");

  /* Call finalize of superclass */
  G_OBJECT_CLASS (t_timer_parent_class) -> finalize (object);
}

static void
t_timer_class_init (TTimerClass *class) {

    GObjectClass *object_class = G_OBJECT_CLASS (class);

    object_class->finalize = t_timer_finalize;

    t_timer_signal =
    g_signal_new_class_handler ("seconds-updated",
                                G_TYPE_FROM_CLASS (class),
                                G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE
                                  | G_SIGNAL_NO_HOOKS,
                                G_CALLBACK (seconds_updated_cb),
                                NULL,
                                NULL,
                                NULL,
                                G_TYPE_NONE,
                                0);

}

static void
t_timer_init (TTimer *self) {
  self->timeout_id = 0;
  self->running = FALSE;
  self->gtimer = g_timer_new ();
  g_debug ("GTimer initialized in TTimer");
}

TTimer*
t_timer_new (void) {
  TTimer* t;

  t = g_object_new (T_TYPE_TIMER, NULL);
  return t;
}



