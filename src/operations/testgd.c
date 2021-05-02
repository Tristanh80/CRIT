#include <gd.h>
#include <stdlib.h>
#include <err.h>

void gs(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageGrayScale(img);
    gdImagePng(img, fdout);
    fclose(fdout);
}


void negate(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageNegate(img);
    gdImagePng(img, fdout);
    fclose(fdout);
}

void emboss(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageEmboss(img);
    gdImagePng(img, fdout);
    fclose(fdout);
}

void contrast(gdImagePtr img, FILE *fdout, char *path, int val)
{
    fdout = fopen(path, "wimg");
    gdImageContrast(img, val);
    gdImagePng(img, fdout);
    fclose(fdout);
}

