#ifndef MOTION_H
#define MOTION_H

#include "preesm.h"

unsigned int SAD(int *ref, int *cur,int blockSize,int width);
void fullSearch(int width, int height, int blockSize, unsigned int *indexOfBlock,unsigned char *input, unsigned char *reference, int *output_x,int *ouput_y);


#endif // MOTION_H
