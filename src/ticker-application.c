/* ticker-application.c
 *
 * Copyright 2024 Aurel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "config.h"

#include "ticker-application.h"
#include "ticker-window.h"

struct _TickerApplication
{
	GtkApplication parent_instance;
};

G_DEFINE_FINAL_TYPE (TickerApplication, ticker_application, GTK_TYPE_APPLICATION)

TickerApplication *
ticker_application_new (const char        *application_id,
                        GApplicationFlags  flags)
{
	g_return_val_if_fail (application_id != NULL, NULL);

	return g_object_new (TICKER_TYPE_APPLICATION,
	                     "application-id", application_id,
	                     "flags", flags,
	                     NULL);
}

static void
ticker_application_activate (GApplication *app)
{
	GtkWindow *window;

	g_assert (TICKER_IS_APPLICATION (app));

	window = gtk_application_get_active_window (GTK_APPLICATION (app));

	if (window == NULL)
		window = g_object_new (TICKER_TYPE_WINDOW, "application", app, NULL);

	gtk_window_present (window);
}

static void
ticker_application_class_init (TickerApplicationClass *klass)
{
	GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

	app_class->activate = ticker_application_activate;
}

static void
ticker_application_about_action (GSimpleAction *action,
                                 GVariant      *parameter,
                                 gpointer       user_data)
{
	static const char *authors[] = {"Aurel Wisse", NULL};
	TickerApplication *self = user_data;
	GtkWindow *window = NULL;
  gchar* gtk_version;

	g_assert (TICKER_IS_APPLICATION (self));

	window = gtk_application_get_active_window (GTK_APPLICATION (self));

  gtk_version = g_strdup_printf ("%s (GTK %d.%d.%d)", PACKAGE_VERSION,
                                 gtk_get_major_version (),
                                 gtk_get_minor_version (),
                                 gtk_get_micro_version ());

	gtk_show_about_dialog (window,
	                       "program-name", "ticker",
	                       "logo-icon-name", APP_ID,
	                       "authors", authors,
	                       "version", gtk_version,
	                       "copyright", "© 2024 Aurel Wisse",
	                       NULL);
}

static void
ticker_application_quit_action (GSimpleAction *action,
                                GVariant      *parameter,
                                gpointer       user_data)
{
	TickerApplication *self = user_data;

	g_assert (TICKER_IS_APPLICATION (self));

	g_application_quit (G_APPLICATION (self));
}

static const GActionEntry app_actions[] = {
	{ "quit", ticker_application_quit_action },
	{ "about", ticker_application_about_action },
};

static void
ticker_application_init (TickerApplication *self)
{
	g_action_map_add_action_entries (G_ACTION_MAP (self),
	                                 app_actions,
	                                 G_N_ELEMENTS (app_actions),
	                                 self);
	gtk_application_set_accels_for_action (GTK_APPLICATION (self),
	                                       "app.quit",
	                                       (const char *[]) { "<primary>q", NULL });
}



