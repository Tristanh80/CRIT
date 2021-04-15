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
#include "../operations/sym.h"
#include "../operations/saturation.h"
#include "../operations/rotate.h"
#include <unistd.h>
#include <sys/wait.h>
// Definition of GTK widget
GtkBuilder *builder;

GtkWidget *image;
GtkWidget *fileChooser;
GtkFileFilter *filterr;



typedef struct {
    GtkWidget *window;
    GtkWidget *w_dlg_file_choose;       // Pointer to file chooser dialog box
    GtkWidget *save_file_choose;        // For save(WIP)
    GtkEntry *bufferSave;               // For save(WIP)
    const gchar *filemaneSave;          // For save (WIP)
    GtkWidget *w_img_main;              // Pointer to image widget
    GtkWidget *ret;                     // For return
    GtkWidget *w_dlg_about;             // For about
    gchar *file_name;                   // Path to the original file
    GtkButton *gScaleButton;            // Button for grayscale
    GtkButton *monochromaticButton;     // Button for monochromatic
    GtkButton *redButton;               // Button for red
    GtkButton *greenButton;             // Button for green
    GtkButton *blueButton;              // Button for blue
    GtkButton *blurButton;              // Button for blur
    GtkButton *borderButton;            // Button for border
    GtkButton *symHor;                  // Button for border
    GtkButton *symVer;                  // Button for border
    GtkButton *satura;                  // Button for border
    GtkButton *rotat;                   // Button for border
    GtkButton *about_close;             // For closing about
    size_t number;                      // Count for CRTLZ

} app_widgets;                          // Our struct for gtk
char* nameOfFile(app_widgets *app_wdgts);

void interface(int argc, char *argv[])
{
    app_widgets *widgets = g_slice_new(app_widgets); // Initialize our struct

    // Init gtk
	gtk_init(&argc, &argv);

	// Connecting glade file
	builder = gtk_builder_new_from_file("src/gtk/interface.glade");
	widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    // Initialize filter for image(bmp for now)
	filterr = gtk_file_filter_new();
	widgets->w_dlg_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_choose"));
    widgets->save_file_choose = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_file_save"));
	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(widgets->w_dlg_file_choose),filterr);
	gtk_file_filter_set_name(filterr,"image");
	gtk_file_filter_add_pattern(filterr,"*.bmp");
    // gtk_file_filter_add_pattern(filterr,"*.jpg");

    // Initialize our variable
	widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->file_name = NULL;
    // WIP
    widgets->bufferSave = GTK_ENTRY(gtk_builder_get_object(builder,"buffer_name"));
    widgets->filemaneSave = NULL;
    // End on WIP
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder,"dlg_about"));
    widgets->ret = GTK_WIDGET(gtk_builder_get_object(builder, "menuitm_return"));
    widgets->gScaleButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_grayscale"));
    widgets->monochromaticButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_monochromatic"));
    widgets->redButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_red"));
    widgets->greenButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_green"));
    widgets->blueButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_blue"));
    widgets->blurButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_blur"));
    widgets->borderButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_border"));
    widgets->symHor = GTK_BUTTON(gtk_builder_get_object(builder, "btn_symhor"));
    widgets->symVer = GTK_BUTTON(gtk_builder_get_object(builder, "btn_symver"));
    widgets->satura = GTK_BUTTON(gtk_builder_get_object(builder, "btn_saturation"));
    widgets->rotat = GTK_BUTTON(gtk_builder_get_object(builder, "btn_rotate"));
    widgets->about_close = GTK_BUTTON(gtk_builder_get_object(builder, "btn_about_close"));
    widgets->number=0;

    // Connect signals with builder
	gtk_builder_connect_signals(builder, widgets);
	g_object_unref(builder);

    // Display application
	gtk_widget_show(widgets->window);

    // Destroy the application properly
    g_signal_connect(widgets->window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();

    // Free our struct
	g_slice_free(app_widgets, widgets);
    
    // Delete temp directory
    int del = system("rm -rf .tmp");
    if(del ==-1)
    {
        errx(1,"Could not delete .tmp directory");
    }
}

// File --> Open
void on_menuitm_open_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    if(menuitem) NULL;
    // Show the "Open Image" dialog box
    gtk_widget_show(app_wdgts->w_dlg_file_choose);
    
    // Check return value from Open Image dialog box to see if user clicked the Open button
    if (gtk_dialog_run(GTK_DIALOG (app_wdgts->w_dlg_file_choose)) == GTK_RESPONSE_OK) {
        // Get the file name from the dialog box
        app_wdgts->file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->w_dlg_file_choose));
        if (app_wdgts->file_name != NULL) {
            // gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
        }

        // Create temp directory
        int tmp = system("mkdir .tmp");
        if (tmp==-1)
        {
            errx(1,"Create tmp directory");
        }

        // Save image in temp directory
        SDL_Surface *image = load_image(app_wdgts->file_name);
        SDL_SaveBMP(image,"temp0.bmp");
        SDL_FreeSurface(image);
        tmp = system("mv temp0.bmp .tmp");
        if (tmp==-1)
        {
            errx(1,"mv in tmp directory");
        }
        
        app_wdgts->file_name = nameOfFile(app_wdgts);
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
        // Set all the widgets sensitive
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->gScaleButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->monochromaticButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->redButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->greenButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->blueButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->blurButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->borderButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->symHor),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->symVer),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->satura),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->rotat),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->ret),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->save_file_choose),TRUE);
    }

    // Finished with the "Open Image" dialog box, so hide it
    gtk_widget_hide(app_wdgts->w_dlg_file_choose);
}

void on_menuitm_saveas_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    if(menuitem) NULL;
    if(app_wdgts->number==0)
    {
        GtkWidget* dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(app_wdgts->window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"You haven't done any actions\n <b>Save impossible. </b>");
		gtk_window_set_title(GTK_WINDOW (dialog), "Problem");
		gtk_dialog_run(GTK_DIALOG (dialog));
		gtk_widget_destroy(dialog);
    }
    else
    {
        gtk_widget_show(app_wdgts->w_dlg_file_choose);
            
            // Check return value from Open Image dialog box to see if user clicked the Open button
            if (gtk_dialog_run(GTK_DIALOG (app_wdgts->save_file_choose)) == GTK_RESPONSE_OK) {
                // Get the file name from the dialog box
                char *filename;
                filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(app_wdgts->save_file_choose));
                printf("%s\n",filename);
                gtk_widget_hide(app_wdgts->save_file_choose);
        }
    }
    
}

char* nameOfFile(app_widgets *app_wdgts)
{
    char buffer[64];
    char temp[32];
    FILE *fp;
    fp = popen("pwd","r");

    if(fgets(buffer, 64, fp) == NULL)
    {
        errx(1,"Error fgets in nameOfFile");
    };
    
    pclose(fp);
    int i = 0;
    char *test = (char *)malloc(sizeof(char)*64);
    while(buffer[i] !=10)
    {
        test[i] = buffer[i];
        i++;
    }
    sprintf(temp,"/.tmp/temp%li.bmp",app_wdgts->number);
    strcat(test,temp);
    return test;
}

// Copy image when one action is made
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
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    greyscale(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
    
}

// Monochromatic function
void on_btn_monochromatic_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    monochromatic(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Red function
void on_btn_red_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    red(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Green function
void on_btn_green_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    green(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Blue function
void on_btn_blue_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    blue(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Blur function
void on_btn_blur_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    blur(image,10);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Border function
void on_btn_border_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    border(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Symhor function
void on_btn_symhor_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    symh(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Symver function
void on_btn_symver_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    symv(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Saturation function
void on_btn_saturation_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    saturation_level(image,'1');                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// rotate function
void on_btn_rotate_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    image = rotate(image,'r');                                          // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Work in progress: return one action before (CRTL+Z)
void on_menuitm_return_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    if(app_wdgts->number==0)
    {
        GtkWidget* dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(app_wdgts->window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"You haven't done any actions\n <b>Return impossible. </b>");
		gtk_window_set_title(GTK_WINDOW (dialog), "Problem");
		gtk_dialog_run(GTK_DIALOG (dialog));
		gtk_widget_destroy(dialog);
    }
    else
    {
        app_wdgts->number-=1;
        app_wdgts->file_name = nameOfFile(app_wdgts);
        gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
        
    }
    
}

// File --> Quit
void on_menuitm_close_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    gtk_main_quit();
}

// About function
void on_menuitm_about_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    gtk_widget_show(app_wdgts->w_dlg_about);
}


void on_btn_about_close_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
    gtk_widget_hide(app_wdgts->w_dlg_about);
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
