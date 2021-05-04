#include <gd.h>
#include <stdlib.h>
#include <stdio.h>
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

void crop(gdImagePtr img, FILE *fdout, char *path, int a, int b)
{
    gdRect *rect = malloc(sizeof(gdRect));
    const int w = gdImageSX(img);
    const int h = gdImageSY(img);
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

/*

void limit(int rgb)
{
    rgb = rgb > 255 ? 255 : rgb;
}

char* itohex(int rgb)
{
    char *color = malloc(sizeof(char)*6);
    sprintf(color, "%06x", rgb);
    printf("%s\n",color);
    return color;
}


void sepia(gdImagePtr img, FILE *fdout, char *path)
{
    fdout = fopen(path, "wb");
    const int w = gdImageSX(img);
    const int h = gdImageSY(img);
    int pixel = 0;

    limit(524);

    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<2; j++)
        {
            pixel = gdImageGetPixel(img, i, j);
            char* color = itohex(pixel);
            free(color);
        }
    }

    gdImageBmp(img, fdout, 0);
    fclose(fdout);

}*/
