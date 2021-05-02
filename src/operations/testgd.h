#ifndef TESTGD_H
#define TESTGD_H

#include <gd.h>

void gs(gdImagePtr img, FILE *fdout, char *path);
void negate(gdImagePtr img, FILE *fdout, char *path);
void emboss(gdImagePtr img, FILE *fdout, char *path);
void contrast(gdImagePtr img, FILE *fdout, char *path, int val);

#endif
