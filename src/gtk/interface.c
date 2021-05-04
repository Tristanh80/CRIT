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
#include "../operations/gdfct.h"
#include <unistd.h>
#include <sys/wait.h>
#include <webkit2/webkit2.h>


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
    GtkWidget *w_dlg_doc;
    GtkWidget *w_webkit_webview;
    GtkWidget *w_dlg_saturation_level;  // For saturation level
    gchar *file_name;                   // Path to the original file
    GtkButton *gScaleButton;            // Button for grayscale
    GtkButton *monochromaticButton;     // Button for monochromatic
    GtkWidget *w_dlg_color;             // Widget for color
    GtkButton *color;                   // Button for widget color
    GtkButton *redButton;               // Button for red
    GtkButton *greenButton;             // Button for green
    GtkButton *blueButton;              // Button for blue
    GtkButton *blurButton;              // Button for blur
    GtkWidget *w_dlg_blur;
    GtkWidget *w_sbtn_quantity_blur;
    GtkWidget *w_dlg_border;
    GtkWidget *w_sbtn_quantity_border;
    GtkButton *borderButton;            // Button for border
    GtkButton *symHor;                  // Button for border
    GtkButton *symVer;                  // Button for border
    GtkButton *satura;                  // Button for border
    GtkButton *rotat;                   // Button for border
    GtkButton *about_close;             // For closing about
    GtkButton *negateButton;
    GtkButton *embossButton;
    GtkWidget *w_dlg_contrast;
    GtkWidget *w_sbtn_quantity_contrast;
    GtkButton *contrastButton;
    GtkButton *cropButton;
    GtkWidget *w_dlg_crop;
    GtkWidget *w_sbtn_quantity_cropx;
    GtkWidget *w_sbtn_quantity_cropy;
    int opentest;
    size_t number;                      // Count for CRTLZ

} app_widgets;                          // Our struct for gtk
char* nameOfFile(app_widgets *app_wdgts);

void interface(int argc, char *argv[])
{
    app_widgets *widgets = g_slice_new(app_widgets); // Initialize our struct

    // Init gtk
	gtk_init(&argc, &argv);

    webkit_web_view_get_type();
    webkit_settings_get_type();

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
    gtk_file_filter_add_pattern(filterr,"*.jpg");
    gtk_file_filter_add_pattern(filterr,"*.jpeg");
    gtk_file_filter_add_pattern(filterr,"*.png");

    // Initialize our variable
	widgets->w_img_main = GTK_WIDGET(gtk_builder_get_object(builder, "img_main"));
    widgets->file_name = NULL;
    // WIP
    widgets->bufferSave = GTK_ENTRY(gtk_builder_get_object(builder,"buffer_name"));
    widgets->filemaneSave = NULL;
    // End on WIP
    widgets->w_dlg_about = GTK_WIDGET(gtk_builder_get_object(builder,"dlg_about"));
    widgets->w_dlg_doc = GTK_WIDGET(gtk_builder_get_object(builder,"dlg_doc"));
    widgets->w_webkit_webview = GTK_WIDGET(gtk_builder_get_object(builder,"webkit_webview"));
    widgets->w_dlg_saturation_level = GTK_WIDGET(gtk_builder_get_object(builder,"dlg_saturation_level"));
    widgets->ret = GTK_WIDGET(gtk_builder_get_object(builder, "menuitm_return"));
    widgets->gScaleButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_grayscale"));
    widgets->monochromaticButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_monochromatic"));
    widgets->w_dlg_color = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_color"));
    widgets->color = GTK_BUTTON(gtk_builder_get_object(builder, "btn_color"));
    widgets->redButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_red"));
    widgets->greenButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_green"));
    widgets->blueButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_blue"));
    widgets->blurButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_blur"));
    widgets->w_dlg_blur = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_blur"));
    widgets->w_sbtn_quantity_blur = GTK_WIDGET(gtk_builder_get_object(builder, "sbtn_blur"));
    widgets->w_dlg_border = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_border"));
    widgets->w_sbtn_quantity_border = GTK_WIDGET(gtk_builder_get_object(builder, "sbtn_border"));
    widgets->borderButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_border"));
    widgets->symHor = GTK_BUTTON(gtk_builder_get_object(builder, "btn_symhor"));
    widgets->symVer = GTK_BUTTON(gtk_builder_get_object(builder, "btn_symver"));
    widgets->satura = GTK_BUTTON(gtk_builder_get_object(builder, "btn_saturation"));
    widgets->rotat = GTK_BUTTON(gtk_builder_get_object(builder, "btn_rotate"));
    widgets->about_close = GTK_BUTTON(gtk_builder_get_object(builder, "btn_about_close"));
    widgets->number=0;
    widgets->negateButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_negate"));
    widgets->embossButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_emboss"));
    widgets->contrastButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_contrast"));
    widgets->w_dlg_contrast = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_contrast"));
    widgets->w_sbtn_quantity_contrast = GTK_WIDGET(gtk_builder_get_object(builder, "sbtn_contrast"));

    widgets->cropButton = GTK_BUTTON(gtk_builder_get_object(builder, "btn_crop"));
    widgets->w_dlg_crop = GTK_WIDGET(gtk_builder_get_object(builder, "dlg_crop"));
    widgets->w_sbtn_quantity_cropx = GTK_WIDGET(gtk_builder_get_object(builder, "sbtn_cropx"));
    widgets->w_sbtn_quantity_cropy = GTK_WIDGET(gtk_builder_get_object(builder, "sbtn_cropy"));

    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(widgets->w_webkit_webview), "https://k4gos.github.io");

    // Connect signals with builder
	gtk_builder_connect_signals(builder, widgets);
	g_object_unref(builder);

    // Display application
	gtk_widget_show(widgets->window);

    // Destroy the application properly
    g_signal_connect(widgets->window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();

    // int dir = system("mkdir imgmodify");
    // if(dir ==-1)
    // {
    //     errx(1,"Could not create imgmodify directory");
    // }
    if(widgets->number!=0)
    {
        SDL_Surface *image = load_image(widgets->file_name);      // Loading image
        SDL_SaveBMP(image,"imgmodify/yourmodifyimage.bmp");
        SDL_FreeSurface(image);
    }
    
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
    if(app_wdgts->opentest != 0)
    {
        app_wdgts-> opentest = 0;
        app_wdgts->number = 0;
        int tst = system("rm -rf .tmp");
        if(tst==-1)
        {
            errx(1,"remove tmp dir");
        }
    }
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
        app_wdgts->opentest+=1;
        // Set all the widgets sensitive
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->gScaleButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->monochromaticButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->color),TRUE);
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
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->negateButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->embossButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->contrastButton),TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(app_wdgts->cropButton),TRUE);
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

void on_btn_color_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_show(app_wdgts->w_dlg_color);
}


// Red function
void on_btn_red_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_hide(app_wdgts->w_dlg_color);
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
    gtk_widget_hide(app_wdgts->w_dlg_color);
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
    gtk_widget_hide(app_wdgts->w_dlg_color);
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    blue(image);                                           // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Blur functions
void on_btn_blur_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_show(app_wdgts->w_dlg_blur);
}

void on_btn_ok_blur_clicked(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    int quantity_blur = 0;
    quantity_blur = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->w_sbtn_quantity_blur));
    gtk_widget_hide(app_wdgts->w_dlg_blur);
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    blur(image,quantity_blur);                                // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

// Border functions
void on_btn_border_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_show(app_wdgts->w_dlg_border);
}


void on_btn_ok_border_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    int quantity_border = 0;
    quantity_border = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->w_sbtn_quantity_border));
    gtk_widget_hide(app_wdgts->w_dlg_border);
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    border(image,quantity_border);                                           // Applied function
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

// Saturation widget
void on_btn_saturation_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_show(app_wdgts->w_dlg_saturation_level);
}

void on_btn_saturation0_clicked(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    gtk_widget_hide(app_wdgts->w_dlg_saturation_level);
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    saturation_level(image,'0');                                // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

void on_btn_saturation1_clicked(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    gtk_widget_hide(app_wdgts->w_dlg_saturation_level);
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    saturation_level(image,'1');                                // Applied function
    copy_image_for_crtlz(app_wdgts);                            // Copy for return
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Update filename
    SDL_SaveBMP(image,app_wdgts->file_name);                    // Save image wit good temp value
    SDL_FreeSurface(image);                                     // Free sdl
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name); // Set the image on application
}

void on_btn_saturation2_clicked(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
	if(menuitem) NULL;
	if(app_wdgts) NULL;
    gtk_widget_hide(app_wdgts->w_dlg_saturation_level);
    app_wdgts->file_name = nameOfFile(app_wdgts);               // Changing filename for temp value
    SDL_Surface *image = load_image(app_wdgts->file_name);      // Loading image
    saturation_level(image,'2');                                // Applied function
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

void on_btn_negate_clicked(GtkButton *widget, app_widgets *app_wdgts)
{
    if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);
    gdImagePtr img = gdImageCreateFromFile(app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
    app_wdgts->file_name= nameOfFile(app_wdgts);
    negate(img, NULL, app_wdgts->file_name);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    gdImageDestroy(img);
}

void on_btn_emboss_clicked(GtkButton *widget, app_widgets *app_wdgts)
{
    if(widget) NULL;
    app_wdgts->file_name = nameOfFile(app_wdgts);
    gdImagePtr img = gdImageCreateFromFile(app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
    app_wdgts->file_name= nameOfFile(app_wdgts);
    emboss(img, NULL, app_wdgts->file_name);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    gdImageDestroy(img);
}

void on_btn_contrast_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_show(app_wdgts->w_dlg_contrast);
}

void on_btn_ok_contrast_clicked(GtkButton *widget, app_widgets *app_wdgts)
{
    if(widget) NULL;
    int quantity_contrast = 0;
    quantity_contrast = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->w_sbtn_quantity_contrast));
    gtk_widget_hide(app_wdgts->w_dlg_contrast);
    app_wdgts->file_name = nameOfFile(app_wdgts);
    gdImagePtr img = gdImageCreateFromFile(app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
    app_wdgts->file_name= nameOfFile(app_wdgts);
    contrast(img, NULL, app_wdgts->file_name, quantity_contrast);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    gdImageDestroy(img);
}

void on_btn_crop_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
	if(widget) NULL;
    gtk_widget_show(app_wdgts->w_dlg_crop);
}

void on_btn_ok_crop_clicked(GtkButton *widget, app_widgets *app_wdgts)
{
    if(widget) NULL;
    int quantity_cropx = 0;
    int quantity_cropy = 0;
    quantity_cropx = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->w_sbtn_quantity_cropx));
    quantity_cropy = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(app_wdgts->w_sbtn_quantity_cropy));
    gtk_widget_hide(app_wdgts->w_dlg_crop);
    app_wdgts->file_name = nameOfFile(app_wdgts);
    gdImagePtr img = gdImageCreateFromFile(app_wdgts->file_name);
    copy_image_for_crtlz(app_wdgts);
    app_wdgts->file_name= nameOfFile(app_wdgts);
    crop(img, NULL, app_wdgts->file_name, quantity_cropx, quantity_cropy);
    gtk_image_set_from_file(GTK_IMAGE(app_wdgts->w_img_main), app_wdgts->file_name);
    gdImageDestroy(img);
}

// Return one action before (CRTL+Z)
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

// About hiding
void on_btn_about_close_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
    if(widget) NULL;
    gtk_widget_hide(app_wdgts->w_dlg_about);
}

void on_menuitm_documentation_activate(GtkMenuItem *menuitem, app_widgets *app_wdgts)
{
    if(menuitem) NULL;
	if(app_wdgts) NULL;
    gtk_widget_show(app_wdgts->w_dlg_doc);
}

void on_btn_close_doc_clicked(GtkButton *widget,app_widgets *app_wdgts)
{
    if(widget) NULL;
    gtk_widget_hide(app_wdgts->w_dlg_doc);
}


// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
