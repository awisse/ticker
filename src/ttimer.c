#define G_LOG_DOMAIN "ttimer-ttimer"
#include "ttimer.h"

static guint t_timer_signal;

/* Add a property to reuse this class with a GTK_WIDGET.
 * Unused in command line mode.  */
enum {
  PROPERTY_0,
  PROPERTY_SECONDS,
  NUM_PROPERTIES
};
/* There is only one property. For the sake of the exercise,
 * no `properties` array of GParamSpec* */
static GParamSpec* sec_prop;

struct _TTimer {
  GObject parent;
  GTimer* gtimer;
  guint counter;
  guint timeout_id;
  gboolean running;
};

G_DEFINE_TYPE (TTimer, t_timer, G_TYPE_OBJECT)

/* Return full seconds elapsed since the start of the timer */
guint
t_timer_get_seconds (TTimer *self, guint *seconds) {
  if (seconds) 
    *seconds = self->counter;
  return self->counter;
}

void
t_timer_start (TTimer *self) {
  if (!self->gtimer) {
    self->gtimer = g_timer_new ();
  } else {
    g_timer_start (self->gtimer);
  }
  self->timeout_id = g_timeout_add (T_TIMER_TIMEOUT,
                                    G_SOURCE_FUNC (t_timer_check), self);

  self->counter = 0;
  self->running = TRUE;
  g_debug ("TTimer started");
}

void
t_timer_stop (TTimer *self) {

  if (!((self->gtimer) && g_timer_is_active (self->gtimer)
        && self->running))
    return;

  g_clear_handle_id (&(self->timeout_id), g_source_remove);
  g_timer_stop (self->gtimer);
  self->running = FALSE;
  g_debug ("TTimer stopped");
}

void
t_timer_reset (TTimer *self) {
    g_timer_reset (self->gtimer);
}

gboolean
t_timer_running (TTimer* self) {
  return self->running;
}
/* Return microseconds elapsed since the start of the timer */
gdouble
t_timer_elapsed (TTimer *self) {
    gdouble elapsed = g_timer_elapsed (self->gtimer, NULL);
    return elapsed;
}

gboolean
t_timer_check (TTimer *self) {

  gdouble elapsed;

  g_assert (self->gtimer);
  elapsed = g_timer_elapsed (self->gtimer, NULL);

  if ((guint)elapsed > self->counter) {
    (self->counter)++;
    g_signal_emit (self, t_timer_signal, 0);
    g_object_notify(G_OBJECT (self), seconds_prop_name);
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
t_timer_get_property (GObject    *object,
                      guint       property_id,
                      GValue     *value,
                      GParamSpec *pspec)
{
  /* There is only one property for now. But for the sake of the exercise,
   * make it a switch */
  TTimer *self = T_TIMER (object);

  switch (property_id) {
    case PROPERTY_SECONDS:
      g_value_set_uint (value, self->counter);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static void
t_timer_class_init (TTimerClass *class) {

  GObjectClass *object_class = G_OBJECT_CLASS (class);


  object_class->get_property = t_timer_get_property;
  object_class->finalize = t_timer_finalize;

  /* Define seconds property */
  sec_prop = g_param_spec_uint (seconds_prop_name, NULL,
                                "Full seconds elapsed since start",
                                0, 0, 0, G_PARAM_READABLE);

  g_object_class_install_property (object_class, PROPERTY_SECONDS, sec_prop);

  t_timer_signal =
  g_signal_new ("seconds-updated",
                G_TYPE_FROM_CLASS (class),
                G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE
                  | G_SIGNAL_NO_HOOKS,
                0,            // class_offset
                NULL,         // accumulator
                NULL,         // accu_data
                NULL,         // c_marshaller
                G_TYPE_NONE,  // return_type
                0);           // n_params
}

static void
t_timer_init (TTimer *self) {
  self->timeout_id = 0;
  self->gtimer = NULL;
  self->running = FALSE;
  g_debug ("GTimer initialized in TTimer");
}

TTimer*
t_timer_new (void) {
  TTimer* t;

  t = g_object_new (T_TYPE_TIMER, NULL);
  return t;
}





