#include "ticker-button.h"
#include "ttimer.h"

void
ticker_on_off (GtkButton *togglebutton,
               gpointer *data)
{
  GtkButton* button = GTK_BUTTON (togglebutton);
  TTimer* timer = T_TIMER (data);

  if (t_timer_running (timer)) {
    t_timer_stop (timer);
    /* Button becomes a start button */
    gtk_button_set_icon_name (button, "media-playback-start-symbolic");
  } else {
    t_timer_start (timer);
    /* Button becomes a stop button */
    gtk_button_set_icon_name(button, "media-playback-stop-symbolic");
  }
}

