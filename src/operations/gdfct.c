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
    struct Queue* next;
}queue;

int queue_is_empty(queue *q)
{
    return q == NULL;
}

queue* queue_push(queue *q, int x, int y)
{
    queue *tmp;
    tmp = malloc(sizeof (struct Queue));
    tmp->x = x;
    tmp->y = y;

    //printf("dans qpush x=%d %d et b=%d %d\n", x, *(tmp->x));

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

queue* queue_pop(queue **q) //return oldest element
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


void bucket(gdImagePtr img, FILE *fdout, char *path, int x, int y, int th, int color)
{
    fdout = fopen(path, "wb");

    th*=2.5;
    int a = 0;  //coord x
    int b = 0;  //coord y
    int c = 0;  //color in (x,y)

    const int w = gdImageSX(img);   //width and height of the image
    const int h = gdImageSY(img);

    int ini = gdImageGetPixel(img, x, y);  //the color to change
    //printf("%d / %d\n",ini,color);

    int ri = gdImageRed(img, ini);
    int bi = gdImageBlue(img,ini);
    int gi = gdImageGreen(img, ini);

    //first element
    gdImageSetPixel(img, x, y, color);
    queue* q = NULL;
    q = queue_push(q, x+1, y);
    //printf("ici q->x=%d", *(q->x));
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

        //printf("a=%d; b= %d; c=%d\n",a,b,c);
        //printf("%d\n", abs(c - ini));

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
        //printf("COUCOU\n");
    }while(!queue_is_empty(q));


    gdImageBmp(img, fdout, 0);
    fclose(fdout);
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

