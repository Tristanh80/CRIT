#include <gd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>


void negate(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wb");
    gdImageNegate(img);

    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

void edges(gdImagePtr img, FILE *fdout, char *path)
{
  fdout = fopen(path, "wb");
  gdImageEdgeDetectQuick(img);
  gdImageBmp(img, fdout, 0);
  fclose(fdout);
}

void emboss(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wb");
    gdImageEmboss(img);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

void contrast(gdImagePtr img, FILE *fdout, char *path, int val)
{
    fdout = fopen(path, "wb");
    gdImageContrast(img, val);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}


void brightness(gdImagePtr img, FILE *fdout, char *path, int val)
{
    fdout = fopen(path, "wb");
    gdImageBrightness(img, val);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}


void crop(gdImagePtr img, FILE *fdout, char *path, int a, int b)
{
    gdRect *rect = malloc(sizeof(gdRect));
    const int w = gdImageSX(img);
    const int h = gdImageSY(img);
    if(a<0 || b<0)
        errx(EXIT_FAILURE, "crop: negative coordinates");
    rect->x = a;
    rect->y = b;
    rect->width = w-2*a;
    rect->height = h-2*b;
    fdout = fopen(path, "wb");
    img = gdImageCrop(img, rect);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
    gdFree(rect);
}



//---------------Bucket and queues-------------------------//

//Circular queue without sentinel is used

//queue structure, x and y of the pixel, next is the next element in the queue
typedef struct Queue
{
    int x;
    int y;
    struct Queue* next;
}queue;


//check if the queue is empty
int queue_is_empty(queue *q)
{
    return q == NULL;
}

//add a new element to the queue
queue* queue_push(queue *q, int x, int y)
{
    queue *tmp;
    tmp = malloc(sizeof (struct Queue));
    tmp->x = x;
    tmp->y = y;

    if(q)
    {
        tmp->next = q->next;
        q->next = tmp;
    }
    else
    {
        tmp->next = tmp;
    }

    return tmp;
}

//return oldest element of the queue
queue* queue_pop(queue **q) 
{
    queue *tmp = (*q)->next;
    if(tmp == tmp->next)
        *q = NULL;
    else
    {
       (*q)->next = tmp->next;
    }
    return tmp;
}


// flood-fill method, choose a pixel and change the color of all the pixels 
// in touch with the first one, and with the same color
// x and y of the pixel, th = threshold of initial color we select, color = the new color
void bucket(gdImagePtr img, FILE *fdout, char *path, int x, int y, int th, int color)
{
    fdout = fopen(path, "wb");

    int a = 0;  //coord x
    int b = 0;  //coord y
    int c = 0;  //color in (x,y)

    const int w = gdImageSX(img);   //width and height of the image
    const int h = gdImageSY(img);

    int ini = gdImageGetPixel(img, x, y);  //the color to change

    int ri = gdImageRed(img, ini);
    int bi = gdImageBlue(img,ini);
    int gi = gdImageGreen(img, ini);

    //first element
    gdImageSetPixel(img, x, y, color);
    queue* q = NULL;
    q = queue_push(q, x+1, y);
    q = queue_push(q, x-1, y);
    q = queue_push(q, x, y+1);
    q = queue_push(q, x, y-1);

    do{
        queue *last = queue_pop(&q);

        a = last->x;
        b = last->y;
        c = gdImageGetPixel(img, a, b);

        int re = gdImageRed(img, c);
        int bl = gdImageBlue(img, c);
        int gr = gdImageGreen(img, c);

        if(abs(re-ri)<=th && abs(gr-gi)<=th && abs(bl-bi)<=th)
        {
            gdImageSetPixel(img, a, b, color);

            if(a-1 >= 0)
                q = queue_push(q, a-1, b);
            if(a+1 < w)
                q = queue_push(q, a+1, b);
            if(b-1 >= 0)
                q = queue_push(q, a, b+1);
            if(b+1 < h)
                q = queue_push(q, a, b-1);
        }

        free(last);

    }while(!queue_is_empty(q));


    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

//--------------------------------------------------------------------------//




//draws a disc in x,y of radius r.
//its color is the average color of the surface covered by the disc
void correct(gdImagePtr img, FILE *fdout, char *path, int x, int y, int r)
{
    fdout = fopen(path, "wb");
    const int w = gdImageSX(img);   // width and height of the image
    const int h = gdImageSY(img);
    int pixel = 0;                  // The chosen pixel
    int n = 0;                      // Number of pixels within the circle

    int red = 0;
    int blue = 0;
    int green = 0;

    int xa = x - r;
    int ya = y - r;

    int xb = x+r;

    int xc = x+r;
    int yc = y+r;

    int yd = y+r;

    if (xa < 0)
    {
        xa = 0;
    }

    else if (ya < 0)
    {
        ya = 0;
    }

    if (xc > w)
    {
        xc = w;
        xb = w;
    }

    else if (yc > h)
    {
        yc = h;
        yd = h;
    }

    for (int i = xa; i < xb; i++){
        for(int j = ya; j < yd; j++){
            if ((i-x)*(i-x)+(j-y)*(j-y) <= r*r){
                pixel = gdImageGetPixel(img, x, y); 
                red += gdImageRed(img, pixel);
                green += gdImageGreen(img, pixel);
                blue += gdImageBlue(img, pixel);
                n++;
            }
        }
    }

    int avred = red/n;
    int avgreen = green/n;
    int avblue = blue/n;

    int color;
    float rnd = 0;

    for (int i = xa; i < xb; i++){
        for(int j = ya; j < yd; j++){
            if ((i-x)*(i-x)+(j-y)*(j-y) <= r*r){
                rnd = (rand()%200)/(float)1000+0.9;

                int cr = (int)((float)avred*rnd);
                int cg = (int)((float)avgreen*rnd);
                int cb = (int)((float)avblue*rnd);

                if(cr>255)
                    cr = 255;
                if(cg>255)
                    cg = 255;
                if(cb>255)
                    cb = 255;

                color = gdImageColorAllocate(img, cr,cg,cb);
                gdImageSetPixel(img, i, j, color);
            }
        }
    }

    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

