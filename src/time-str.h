/* Convert a number of seconds into a time label of the form:
 * [hh]:[mm]:ss
 */
#pragma once
#include <glib.h>
#include "ttimer.h"

char* format_time (guint total);
