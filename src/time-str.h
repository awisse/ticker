/* Convert a number of seconds into a time label of the form:
 * [hh]:[mm]:ss
 */
#pragma once
#include <glib.h>
#include "ttimer.h"

GString*
format_time (gint64 total);

// void
// update_label (TTimer *timer, )
