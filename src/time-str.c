/* Format the time for the time label */
#include "time-str.h"

/* Transform the number of seconds `total` into an hh:mm:ss string
 * without leading zeros. The caller is responsible for freeing the
 * return value */
GString* format_time (gint64 total) {

  GString* gstr;
  gint64 seconds, minutes, hours;
  gsize length;
  gssize erased;

  gstr = g_string_sized_new (9);

  seconds = total % 60;
  minutes = (total / 60) % 60;
  hours = (total / 3600);

  if (hours > 99) {
    gstr = g_string_assign (gstr, "--:--:--");
    return gstr;
  }

  g_string_printf (gstr, "%ld:%02ld:%02ld", hours, minutes, seconds);
  length = gstr->len;

  if (total < 10) {
    erased = length - 1;
  } else if (total < 60) {
    erased = length - 2;
  } else if (total < 600) {
    erased = length - 4;
  } else if (total < 3600) {
    erased = length - 5;
  } else {
    erased = 0;
  }

  gstr = g_string_erase (gstr, 0, erased);

  return gstr;

}

