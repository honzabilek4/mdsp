#ifndef SPLIT_MERGE_H
#define SPLIT_MERGE_H

#include "preesm.h"

/**
* @param blockSize
*        the size of a square block
* @param width
*        the width of the input image
* @param height
*        the height of the input image
* @param input
*        the input image of size width*height
* @param output
*        the output buffer of size blockSize*blockSize
* @param blockIndex
*        index of currently processed block
*/
void split(int blockSize, int width, int height, IN unsigned char *input, OUT unsigned char *output, OUT int *blockIndex);

/**
*
* @param blockSize
*        the size of a square block
* @param width
*        the width of the output image
* @param height
*        the height of the output image
* @param input
*        the input image blocks
* @param output
*        the output image of size width*height
* @param mv
*        motion vector determining the domimant movement
*/
void merge(int blockSize, int width, int height,IN unsigned char *input,OUT unsigned char *output,IN int *mv);

#endif
