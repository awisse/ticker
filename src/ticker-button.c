#include "ticker-button.h"

void
ticker_on_off (GtkToggleButton *button,
               GVariant *parameter G_GNUC_UNUSED,
               gpointer *data) {

  char label[6] = "Start";

  if (gtk_toggle_button_get_active (button))
    strcpy(label, "Stop");

  g_print("Label: %s\n", label);

  gtk_button_set_label (GTK_BUTTON (button), label);

}
