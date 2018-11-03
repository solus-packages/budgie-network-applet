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

static void setAllMargins(GtkWidget *widget, gint size) {
     gtk_widget_set_margin_top(widget, size);
     gtk_widget_set_margin_start(widget, size);
     gtk_widget_set_margin_end(widget, size);
     gtk_widget_set_margin_bottom(widget, size);
}


/* Create a Section Header pseudo Widget
 *
 * @param name      - the name of the section
 * @param icon_name - the name of the icon to use for this section
 *
 * @returns the newly built section header widget
 */
static GtkWidget * createSectionHeader(const gchar* name, const gchar* icon_name) {
    GtkWidget *header;
    GtkWidget *toggle;
    GtkWidget *label;

    /* Build the icon */
    toggle  = gtk_button_new_from_icon_name(icon_name, GTK_ICON_SIZE_MENU);

    /* Build the label a left-align the text */
    label = gtk_label_new(name);
    gtk_widget_set_halign(label, GTK_ALIGN_START);


    /* Construct a horizontal box with the two widgets */
    header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    /* Add the toggle as centered with 5-pixel padding */
    gtk_box_pack_start(GTK_BOX(header), toggle, FALSE, FALSE, 5);
    /* Add the label as expaned with 5-pixel padding */
    gtk_box_pack_start(GTK_BOX(header), label, TRUE, TRUE, 5);

    return header;
}

/* Create a Section pseudo Widget
 *
 * @param name      - the name of the section
 * @param icon_name - the name of the icon to use for this section
 *
 * @returns the newly built section widget
 */
static GtkWidget * createSection(const gchar* name, const gchar* icon_name) {
    GtkWidget *section;
    GtkWidget *header;
    GtkWidget *separator;

    header = createSectionHeader(name, icon_name);
    separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_margin_top(separator, 5);

    section = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    setAllMargins(section, 5);
    gtk_container_add(GTK_CONTAINER(section), header);
    gtk_container_add(GTK_CONTAINER(section), separator);

    return section;
}

static GtkWidget * createSettingsWidget() {
    GtkWidget *settings;
    GtkWidget *pad1;
    GtkWidget *pad2;
    GtkWidget *network;
    GtkWidget *vpn;

    pad1 = gtk_label_new("");
    gtk_widget_set_hexpand(pad1,TRUE);
    pad2 = gtk_label_new("");
    gtk_widget_set_hexpand(pad2,TRUE);

    network  = gtk_button_new_from_icon_name("preferences-system-symbolic", GTK_ICON_SIZE_MENU);
    setAllMargins(network, 5);

    vpn      = gtk_button_new_from_icon_name("network-vpn-symbolic", GTK_ICON_SIZE_MENU);
    setAllMargins(vpn, 5);

    settings = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(settings), pad1);
    gtk_container_add(GTK_CONTAINER(settings), network);
    gtk_container_add(GTK_CONTAINER(settings), vpn);
    gtk_container_add(GTK_CONTAINER(settings), pad2);

    return settings;
}
/* Build the test window and setup the applet inside of it
 *
 * @param app       - the application object for this instance
 * @param user_data - unused
 */
static void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *wired_section;
    GtkWidget *wifi_section;
    GtkWidget *wlan_section;
    GtkWidget *settings;

    wired_section = createSection("Wired Connections",    "network-wired-symbolic");
    wifi_section  = createSection("WiFi Connections",     "network-wireless-symbolic");
    wlan_section  = createSection("Cellular Connections", "network-cellular-signal-excellent-symbolic");

    settings = createSettingsWidget();

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(box), wired_section);
    gtk_container_add(GTK_CONTAINER(box), wifi_section);
    gtk_container_add(GTK_CONTAINER(box), wlan_section);
    gtk_container_add(GTK_CONTAINER(box), settings);

    window = gtk_application_window_new (app);
    gtk_window_set_title(GTK_WINDOW(window), "Testing Network Applet");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, -1);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
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
