/* Define a struct that holds timer data
 */
#include <gtk/gtk.h>

typedef struct _timer {
  gint64 start_time;
  gint64 stepsize;
  gint64 steps;
} Timer;

gboolean next_step (Timer* timer);
