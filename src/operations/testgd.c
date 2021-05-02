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


