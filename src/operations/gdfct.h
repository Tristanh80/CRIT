#ifndef GDFCT_H
#define GDFCT_H

#include <gd.h>

void negate(gdImagePtr img, FILE *fdout, char *path);
void emboss(gdImagePtr img, FILE *fdout, char *path);
void contrast(gdImagePtr img, FILE *fdout, char *path, int val);
void crop(gdImagePtr img, FILE *fdout, char *path, int a, int b);
void brightness(gdImagePtr img, FILE *fdout, char *path, int val);

#endif
