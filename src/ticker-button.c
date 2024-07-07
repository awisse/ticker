#include "ticker-button.h"
#include "ticking.h"

void
ticker_on_off (GtkToggleButton *togglebutton,
               GVariant *parameter G_GNUC_UNUSED,
               gpointer *data G_GNUC_UNUSED)
{
  GtkButton* button = GTK_BUTTON (togglebutton);
  static guint timeout_id = 0;
  static gboolean playing = FALSE;

  if (!playing) {
    /* Start clicking once per second */
    if (start_ticking () == -1) {
      g_printerr ("Couldn't allocate memory for timer\n");
      return;
    }
    timeout_id = g_timeout_add (10, G_SOURCE_FUNC (update_tick), button);

    /* Button becomes a stop button */
    gtk_button_set_icon_name(button, "media-playback-stop-symbolic");
    playing = TRUE;
  } else {
    if (!g_source_remove (timeout_id)) {
      g_printerr ("Timeout Removal Failed!\n");
    }
    stop_ticking ();

    /* Button becomes a start button */
    gtk_button_set_icon_name (button, "media-playback-start-symbolic");
    playing = FALSE;
  }
}
