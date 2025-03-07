#pragma once

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600

static void syncLoadSignal(GtkApplication *app,gpointer userdata){
    GtkWidget *window;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Application.name");
    gtk_window_set_default_size(GTK_WINDOW(window),WIDTH,HEIGHT);

    button = gtk_button_new_with_label("Loading Data");
    gtk_window_set_child(GTK_WINDOW(window),button);
    gtk_window_present(GTK_WINDOW(window));
}

static int constructApplication(int argc, char **argv){
    GtkApplication *application;
    int status;
    application = gtk_application_new("DataProject.exe",G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(application,"activate",G_CALLBACK(syncLoadSignal),NULL);
    status = g_application_run(G_APPLICATION(application),argc,argv);
    g_object_unref(application);
    return status;
}
