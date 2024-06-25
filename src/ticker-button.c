#include "ticker-button.h"
#include "ticking.h"

void
ticker_on_off (GtkToggleButton *button,
               GVariant *parameter G_GNUC_UNUSED,
               gpointer *data G_GNUC_UNUSED)
{
  char label[6] = "Start";
  static guint timeout_id = 0;

  if (gtk_toggle_button_get_active (button)) {
    /* Button becomes a stop button */
    strcpy(label, "Stop");
    /* Start clicking once per second */
    timeout_id = g_timeout_add_seconds (1, G_SOURCE_FUNC (play_tick), NULL);
  } else {
    if (!g_source_remove (timeout_id)) {
      g_print ("Timeout Removal Failed!\n");
    }
  }

  gtk_button_set_label (GTK_BUTTON (button), label);

}
