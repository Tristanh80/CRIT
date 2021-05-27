#include <gd.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>


void negate(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wb");
    gdImageNegate(img);


    //TESTS A ENLEVER
    /*for(int x = 16770000; x<16777215; x++)
    {
        gdImageColorReplace(img,x,16711680);
    }
    gdImageFile(img, "testColor.jpg");*/

    /*
    gdImageBoundsSafe(img, 100, 100);
    gdImageFile(img, "testBounds.jpg");
    */

    /*
    gdImageChar(img, NULL, 100, 100, 64, 0);
    gdImageFile(img, "testChar.jpg");
    */

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

typedef struct Queue
{
    int x;
    int y;
    struct queue* next;
}queue;

int queue_is_empty(queue *q)
{
    return q == NULL;
}

void queue_push(queue *q, int x, int y)
{
    queue *tmp;
    tmp = malloc(sizeof (struct queue));
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

queue* queue_pop(queue **q)//return oldest element
{
    queue *tmp = (*q)->next;
    void *x = tmp->x;
    void *y = tmp->y;
    if(tmp == tmp->next)
        *q = NULL;
    else
        *q->next = tmp->next;
    return tmp;
}


void bucket(gdImagePtr img, FILE *fdout, char *path, int x, int y, int th, int color)
{
    th*=5;
    inicolor = gdImageGetPixel(img, x, y);  //the color to change

    int a = 0;  //coord x
    int b = 0;  //coord y
    int c = 0;  //color in (x,y)

    //first element
    gdImageSetPixel(img, x, y, color);
    queue* q = NULL;
    q = queue_push(q, x+1, y);
    q = queue_push(q, x-1, y);
    q = queue_push(q, x, y+1);
    q = queue_push(q, x, y-1);

    do{
        queue *q = queue_pop(&q);

        a = q->x;
        b = q->y;
        c = gdImageGetPixel(img, a, b);

        if(abs(c - inicolor) <= th)
        {
            gdImageSetPixel(img, a, b, color);

            q = queue_push(q, a+1, b);
            q = queue_push(q, a-1, b);
            q = queue_push(q, a, b+1);
            q = queue_push(q, a, b-1);
        }

        free(q);

    }while(!queue_is_empty(q));
}

//--------------------------------------------------------------------------//




/*
void correct(gdImagePtr img, FILE *fdout, char *path, int x, int y, int a, int b)
{
    fdout = fopen(path, img);
    int arr[3][3] = {{0, 0, 0},{0, 0, 0},{0, 0, 0}};

    if(abs(y-b) > abs(x-a))
    {
        arr = {{1, 0, 1},{2, 0, 2},{1, 0, 1}};
    }

    else
    {
        arr = {{1, 2, 1},{0, 0, 0},{1, 2, 1}};
    }

    while(x!=a && y!=b)
    {

        gdImageSetPixel(img, x, y, color);
    }
    dgImageBmp(img, fdout, 0);
    fclose(fdout);
}*/

