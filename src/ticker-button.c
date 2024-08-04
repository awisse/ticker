#include "ticker-button.h"
#include "ttimer.h"

void
ticker_on_off (GtkButton *togglebutton,
               gpointer *data)
{
  GtkButton* button = GTK_BUTTON (togglebutton);
  GtkLabel* label = GTK_LABEL (gtk_button_get_child(button));
  TTimer* timer = T_TIMER (data);

  if (t_timer_running (timer)) {
    t_timer_stop (timer);
    /* Button becomes a start button */
    gtk_label_set_text (label, "Start");
  } else {
    t_timer_start (timer);
    /* Button becomes a stop button */
    gtk_label_set_text (label, "Stop");
  }
}


