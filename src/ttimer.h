#pragma once

#include <gio/gio.h>

#define T_TYPE_TIMER (t_timer_get_type ())
G_DECLARE_FINAL_TYPE (TTimer, t_timer, T, TIMER, GObject)

/* get elapsed full seconds */
guint
t_timer_get_seconds(TTimer *self, guint *seconds);

/* Public methods */
void
t_timer_start (TTimer *self);

void
t_timer_stop (TTimer *self);

void
t_timer_reset (TTimer *self);

/* Return microseconds elapsed since the start of the timer */
gdouble
t_timer_elapsed (TTimer *self);

/* GSourceFunc: Check whether a second has elapsed. Must be called
 * regularly from the main loop */
gboolean
t_timer_check (TTimer *self);

/* Create instance */
TTimer*
t_timer_new (void);
