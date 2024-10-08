/* main.c
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

#define G_LOG_DOMAIN "ticker-main"
#include "config.h"

#include <glib/gi18n.h>

#include "ticker-application.h"

int
main (int   argc,
      char *argv[])
{
  g_autoptr(TickerApplication) app = NULL;
  int ret;

  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);

  /* Display Glib version to know where we stand on the
   * platform this is built on */
  g_info("GLib version: %d.%d.%d\n", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION,
          GLIB_MICRO_VERSION);

  /* Display GTK version to know where we stand on the
   * platform this is built on */
  g_info("GTK version: %d.%d.%d\n", GTK_MAJOR_VERSION, GTK_MINOR_VERSION,
          GTK_MICRO_VERSION);

#if GLIB_CHECK_VERSION (2, 74, 0)
  app = ticker_application_new (APP_ID, G_APPLICATION_DEFAULT_FLAGS);
#else
  app = ticker_application_new (APP_ID, G_APPLICATION_FLAGS_NONE);
#endif
  ret = g_application_run (G_APPLICATION (app), argc, argv);

  return ret;
}



