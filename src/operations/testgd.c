#include <gd.h>
#include <stdlib.h>
#include <err.h>

void(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wimg");
    gdImageGrayScale(img);
    gdImagePng(img, fdout);
    fclose(fdout);
}
