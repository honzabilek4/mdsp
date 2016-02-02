#ifndef MOTION_H
#define MOTION_H

#include "preesm.h"

unsigned long SAD(unsigned char *ref, unsigned char *cur,int blockSize,int width);
void fullSearch(int width, int height, int blockSize,IN int *blockIndex,IN unsigned char *input,IN unsigned char *reference,OUT int *output_x,OUT int *output_y);


#endif // MOTION_H
