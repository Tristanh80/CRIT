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

