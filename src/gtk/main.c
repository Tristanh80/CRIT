//#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

// Definition of GTK widget
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *image;
GtkWidget *fileChooser;
GtkFileChooser *f;
GtkFileFilter *filter;
char *file;



typedef struct {
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *w_img_main;              // Pointer to image widget
} app_widgets;


int main(int argc, char *argv[])
{
	app_widgets *widgets = g_slice_new(app_widgets);
	gtk_init(&argc, &argv);

	// Connecting glade file and file chooser
	builder = gtk_builder_new_from_file("interface.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	filter = gtk_file_filter_new();
	widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(widgets->w_dlg_file_choose),filter);
	gtk_file_filter_set_name(filter,"image");
	gtk_file_filter_add_pattern(filter,"*.bmp");
	widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));

	gtk_builder_connect_signals(builder, widgets);

	g_object_unref(builder);

	gtk_widget_show(window);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();
	g_slice_free(app_widgets, widgets);
	


	return 0;
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (file_name != NULL) {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), file_name);
        }
        g_free(file_name);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    gtk_main_quit();
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}