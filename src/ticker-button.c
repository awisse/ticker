#include "ticker-button.h"
#include "ticking.h"

void
ticker_on_off (GtkToggleButton *togglebutton,
               GVariant *parameter G_GNUC_UNUSED,
               gpointer *data G_GNUC_UNUSED)
{
  GtkButton* button = GTK_BUTTON (togglebutton);
  static guint timeout_id = 0;

  if (gtk_toggle_button_get_active (togglebutton)) {
    /* Button becomes a stop button */
    gtk_button_set_label(button, "Stop");
    /* Start clicking once per second */
    if (start_ticking () == -1) {
      g_printerr ("Couldn't allocate memory for timer\n");
      return;
    }
    timeout_id = g_timeout_add (10, G_SOURCE_FUNC (update_tick), button);
  } else {
    if (!g_source_remove (timeout_id)) {
      g_printerr ("Timeout Removal Failed!\n");
    }
    stop_ticking ();
    gtk_button_set_label (button, "Start");
  }



}
