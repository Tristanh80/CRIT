#include <gd.h>
#include <stdlib.h>
#include <err.h>

/*
void gs(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "w");
    gdImageGrayScale(img);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}*/


void negate(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wb");
    gdImageNegate(img);
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

void crop(gdImagePtr img, FILE *fdout, char *path)
{
    gdRect *rect = malloc(sizeof(gdRect));
    rect->x = 0;
    rect->y = 0;
    rect->width = 20;
    rect->height = 20;
    fdout = fopen(path, "wb");
    img = gdImageCrop(img, rect);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
    gdFree(rect);
}
