#ifndef MOTION_H
#define MOTION_H

#include "preesm.h"

unsigned int SAD(int *ref, int *cur,int blockSize,int width);
void fullSearch(int width, int height, int blockSize, IN unsigned char *input, IN unsigned char *reference, OUT unsigned char *output)


#endif // MOTION_H
