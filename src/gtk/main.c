//#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Definition of GTK widget
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *fileChooser;
GtkFileChooser *f;
GtkFileFilter *filter;
char *file;




int main(int argc, char *argv[])
{

	gtk_init(&argc, &argv);

	// Connecting glade file and file chooser
	builder = gtk_builder_new_from_file("interface.glade");
	gtk_builder_connect_signals(builder, NULL);
	//GError* error = NULL;
	//if(gtk_builder_new_from_file(builder, "interface.glade", &error) == 0)
	//{
	//	g_printerr("Error loading file: %s\n", error->message);
	//	g_clear_error(&error);
	//	return 1;
	//}	
	filter = gtk_file_filter_new();
	fileChooser = GTK_WIDGET(gtk_builder_get_object(builder, "fileChooser"));
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fileChooser),filter);
	gtk_file_filter_set_name(filter,"image");
	gtk_file_filter_add_pattern(filter,"*.bmp");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "shotopof"));
	f = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "f"));


	gtk_file_filter_set_name(filter,"image");
	gtk_file_filter_add_pattern(filter,"*.bmp");

	//window = GTK_WINDOW(gtk_builder_get_object(builder, "org.gtk.shotopof"));
	//f = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "f"));

	g_object_unref(builder);
	gtk_widget_show(window);

	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);

	gtk_main();

	return 0;
}
