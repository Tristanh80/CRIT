#include <gd.h>
#include <stdlib.h>
#include <err.h>

void gs(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageGrayScale(img);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}


void negate(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageNegate(img);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

void emboss(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageEmboss(img);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

void contrast(gdImagePtr img, FILE *fdout, char *path, int val)
{
    fdout = fopen(path, "wimg");
    gdImageContrast(img, val);
    gdImageBmp(img, fdout, 0);
    fclose(fdout);
}

