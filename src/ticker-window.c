/* ticker-window.c
 *
 * Copyright 2024 Aurel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define G_LOG_DOMAIN "ticker-window"
#include "config.h"

#include "ticker-window.h"
#include "ticker-button.h"
#include "ttimer.h"
#include "time-str.h"
#include "click.h"

struct _TickerWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar  *header_bar;
  GtkLabel      *label;
  GtkButton     *start_stop;

  /* Model */
  TTimer *timer;
};

G_DEFINE_FINAL_TYPE (TickerWindow, ticker_window, GTK_TYPE_APPLICATION_WINDOW)

static void
ticker_window_class_init (TickerWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/ca/awisse/ticker/ticker-window.ui");
  gtk_widget_class_bind_template_child (widget_class, TickerWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, TickerWindow, label);
  gtk_widget_class_bind_template_child (widget_class, TickerWindow, start_stop);

}

static char*
time_to_char (GObject *object, guint total, gpointer unused)
{
  return format_time (total);
}

static void
bind_seconds_to_label (TickerWindow *self)
{
  GtkExpression *expression, *timer_expression;

  /* Transform timer into an expression */
  timer_expression = gtk_constant_expression_new (T_TYPE_TIMER, self->timer);

  /* Get the `seconds_prop_name` property as an expression, which is
   * a guint in seconds. */
  expression = gtk_property_expression_new (T_TYPE_TIMER,
                                            gtk_expression_ref (timer_expression),
                                            seconds_prop_name);

  /* Transform the guint into a string to be inserted into the label */
  expression = gtk_cclosure_expression_new (G_TYPE_STRING, NULL, 1,
                                            (GtkExpression *[1]){expression},
                                            G_CALLBACK (time_to_char),
                                            NULL, NULL);

  /* Bind the expression to the label */
  gtk_expression_bind (expression, self->label, "label", self->label);

}

static void
ticker_window_init (TickerWindow *self)
{

  gtk_widget_init_template (GTK_WIDGET (self));

  /* Create timer */
  self->timer = t_timer_new();

  g_signal_connect (self->start_stop, "clicked",
                    G_CALLBACK (ticker_on_off), self->timer);

  g_signal_connect (self->timer, "seconds-updated",
                    G_CALLBACK (click_cb), NULL);

  /* Add expression to self->label for automatic update */
  bind_seconds_to_label (self);

  /* Test format_time */
  g_debug ("format_time(100h) = %s", format_time (100 * 60 * 60));

}

