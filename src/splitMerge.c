#include <string.h>
#include <stdlib.h>

#include "splitMerge.h"

void split(int blockSize, int width, int height, unsigned char *input, unsigned char *output) {

	int i, j, k;
	unsigned char *p_in = input;
	unsigned char *p_out = output;

	for (i = 0; i <= height / blockSize; i++)
	{
		for (j = 0; j <= width / blockSize; j++)
		{
			for (k = 0; k < blockSize; k++)
			{
				memcpy(p_out, p_in + k*width, blockSize); //copy one block line to output
				p_out += blockSize; //increment output pointer per one block line
			}
			p_in += j*blockSize;
		}
		p_in = input + i*blockSize*width;
	}

}


void merge(int blockSize, int width, int height, unsigned char *input, unsigned char *output) {
	int i, j, k;
	unsigned char *p_in = input;
	unsigned char *p_out = output;
    int	frameSize = width*height;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			for (k = 0; k < frameSize/(blockSize*blockSize); k++)
			{
				memcpy(p_out, p_in, blockSize); //copy one block line to output
				p_out += blockSize; //increment output pointer per one block line
				p_in += j*blockSize*blockSize;
			}
		}
		p_in = input + i* blockSize*blockSize;
	}
}
