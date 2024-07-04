/*
 * Manage the events received by the ticker button
 */
#pragma once

#include <gtk/gtk.h>

void
ticker_on_off (GtkToggleButton *button, GVariant *parameter, gpointer* data);
