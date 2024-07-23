/* Convert a number of seconds into a time label of the form:
 * [hh]:[mm]:ss
 */
#pragma once
#include <glib.h>

GString*
format_time (gint64 total);
