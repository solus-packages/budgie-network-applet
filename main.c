/*
 * Copyright 2018 Bryan T. Meyers <bryan@getsol.us>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http: *www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtk/gtk.h>

static GtkWidget * createSectionHeader(const gchar* name, const gchar* icon_name) {
    GtkWidget *header;
    GtkWidget *icon;
    GtkWidget *label;

    icon  = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_MENU);

    label = gtk_label_new(name);
    gtk_widget_set_halign(label, GTK_ALIGN_START);

    header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(header), icon, FALSE, FALSE, 5);
    //gtk_container_add(GTK_CONTAINER(header), icon);
    gtk_box_pack_start(GTK_BOX(header), label, TRUE, TRUE, 5);
    //gtk_container_add(GTK_CONTAINER(header), label);
    return header;
}

/* Build the test window and setup the applet inside of it
 *
 * @param app       - the application object for this instance
 * @param user_data - unused
 */
static void activate(GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *wired_header;
  GtkWidget *wifi_header;
  GtkWidget *wlan_header;

  wired_header = createSectionHeader("Wired Connections", "network-wired-symbolic");
  wifi_header = createSectionHeader("WiFi Connections", "network-wireless-symbolic");
  wlan_header = createSectionHeader("Cellular Connections", "network-cellular-signal-excellent-symbolic");

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(box), wired_header);
  gtk_container_add(GTK_CONTAINER(box), wifi_header);
  gtk_container_add(GTK_CONTAINER(box), wlan_header);

  window = gtk_application_window_new (app);
  gtk_window_set_title(GTK_WINDOW (window), "Testing Network Applet");
  gtk_window_set_default_size(GTK_WINDOW (window), 200, 200);
  gtk_container_add(GTK_CONTAINER(window), box);

  gtk_widget_show_all(window);
}

/* Main
 *
 * @param argc - the number of arguments in argv
 * @param argv - the command-line arguments for this application
 *
 * @returns the status code
 */
int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.budgie-desktop.applet.network", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run(G_APPLICATION (app), argc, argv);
  g_object_unref(app);

  return status;
}
