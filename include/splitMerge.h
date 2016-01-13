#ifndef SPLIT_MERGE_H
#define SPLIT_MERGE_H

#include "preesm.h"

void split(int blockSize, int width, int height, IN unsigned char *input, OUT unsigned char *output);

void merge(int blockSize, int width, int height, IN unsigned char *input, OUT unsigned char *output);

#endif
