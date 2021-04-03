#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "../import/import.h"
#include "../operations/grey.h"
#include "../operations/filters.h"
#include "../operations/blur.h"
#include "../operations/border.h"

// Definition of GTK widget
GtkBuilder *builder;
GtkWidget *window;
GtkWidget *image;
GtkWidget *fileChooser;
// GtkButton *gScaleButton;
// GtkButton *Bmonochromatic;
GtkFileFilter *filterr;
char *file;



typedef struct {
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *w_img_main;              // Pointer to image widget
    gchar *file_name;                   // Path to the original file
    GtkButton *gScaleButton;            // Button for grayscale
    GtkButton *monochromaticButton;     // Button for monochromatic
    GtkButton *redButton;               // Button for red
    GtkButton *greenButton;             // Button for green
    GtkButton *blueButton;              // Button for blue
    GtkButton *blurButton;              // Button for blur
    GtkButton *borderButton;            // Button for border
    size_t number;                      // Count for CRTLZ

} app_widgets;                          // Our struct for gtk


void interface(int argc, char *argv[])
{
    app_widgets *widgets = g_slice_new(app_widgets); // Initialize our struct

    // Init gtk
	gtk_init(&argc, &argv);

	// Connecting glade file
	builder = gtk_builder_new_from_file("gtk/interface.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    // Initialize filter for image(bmp for now)
	filterr = gtk_file_filter_new();
	widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(widgets->w_dlg_file_choose),filterr);
	gtk_file_filter_set_name(filterr,"image");
	gtk_file_filter_add_pattern(filterr,"*.bmp");
    // gtk_file_filter_add_pattern(filterr,"*.jpg");

    // Initialize our variable
	widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->file_name = NULL;
    widgets->gScaleButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_grayscale"));
    widgets->monochromaticButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_monochromatic"));
    widgets->redButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_red"));
    widgets->greenButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_green"));
    widgets->blueButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_blue"));
    widgets->blurButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_blur"));
    widgets->borderButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_border"));
    widgets->number=0;

	gtk_builder_connect_signals(builder, widgets);

	g_object_unref(builder);

	gtk_widget_show(window);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();
	g_slice_free(app_widgets, widgets);
    
    int del = system("rm -rf .tmp");
    if(del ==-1)
    {
        errx(1,"Could not delete .tmp directory");
    }
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    // gchar *file_name = NULL;        // Name of file to open from dialog box
    
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        app_wdgts->file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (app_wdgts->file_name != NULL) {
            gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
            printf("%s",app_wdgts->file_name);
        }
        int tmp = system("mkdir .tmp");
        if (tmp==-1)
        {
            errx(1,"Create tmp directory");
        }
        SDL_Surface *image = load_image(app_wdgts->file_name);
        SDL_SaveBMP(image,"temp0.bmp");
        SDL_FreeSurface(image);
        tmp = system("mv temp0.bmp .tmp");
        if (tmp==-1)
        {
            errx(1,"Create tmp directory");
        }
        app_wdgts->file_name = ".tmp/temp0.bmp";
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main),app_wdgts->file_name);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->gScaleButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->monochromaticButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->redButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->greenButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->blueButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->blurButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->borderButton),TRUE);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

void copy_image_for_crtlz(app_widgets *app_wdgts)
{
    char cmd[128];
    sprintf(cmd,"cp %s .tmp/temp%li.bmp",app_wdgts->file_name,app_wdgts->number+1);
    int cp = system(cmd);
    if(cp ==-1)
    {
        errx(1,"Error in copy for crtlz");
    }
    app_wdgts->number +=1;
}

// Grayscale function
void on_btn_grayscale_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    greyscale(image);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
    
}

void on_btn_monochromatic_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    monochromatic(image);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
}

void on_btn_red_clicked(GtkMenuItem *menuitem,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    red(image);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
}

void on_btn_green_clicked(GtkMenuItem *menuitem,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    green(image);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
}

void on_btn_blue_clicked(GtkMenuItem *menuitem,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    blue(image);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
}

void on_btn_blur_clicked(GtkMenuItem *menuitem,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    blur(image,10);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
}

void on_btn_border_clicked(GtkMenuItem *menuitem,app_widgets *app_wdgts)
{
    SDL_Surface *image = load_image(app_wdgts->file_name);
    border(image);
    SDL_SaveBMP(image,app_wdgts->file_name);
    SDL_FreeSurface(image);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
}

void on_menuitm_return_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    char cmd[128];
    if(app_wdgts->number==0)
    {
        errx(1,"You haven't done any action");
    }
    else
    {
        printf("%s",app_wdgts->file_name);
        sprintf(cmd,".tmp/temp%li.bmp",app_wdgts->number);
        app_wdgts->file_name=cmd;
        printf("%s",app_wdgts->file_name);
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
        app_wdgts->number-=1;
    }
    
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