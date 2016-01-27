#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "splitMerge.h"


//frame is divided into the blocks blockSize x blockSize
//direction is from the most left to the right block per block-row
//within each block pixels are copied per row
void split(int blockSize, int width, int height, unsigned char *input, unsigned char *output, int* blockIndex)
{

	int i, j, k;
	unsigned char *p_in;
	unsigned char *p_row;
	int pixFillHeight = blockSize - (height%blockSize); //compute resting pixels to be filled in, in order to make frame dividable by blockSize
	int pixFillWidth  = blockSize - (width%blockSize) ;
	int heightF = height + pixFillHeight; //get filled size
	int widthF = width + pixFillWidth;
	int fillHeight = 0; //dynamic variables, depend on actual loop
	int fillWidth = 0;

	for (i = 0; i < heightF / blockSize; i++)
	{
		p_row = input + i*blockSize*width;

		for (j = 0; j < widthF / blockSize; j++)
		{
			p_in = p_row + j*blockSize;

			fillHeight = i == (height / blockSize) ? pixFillHeight : 0;
			fillWidth = j == (width / blockSize) ? pixFillWidth : 0;
            memset(blockIndex + )
			for (k = 0; k < blockSize - fillHeight; k++) //ordinal loop
			{
				memcpy(output, p_in + k*width, blockSize - fillWidth); //copy pixels to output
				memset(output + (blockSize - fillWidth), 0, fillWidth); // fill the last block to size of blockSize
				output += blockSize; //increment output pointer per one block line
			}
			for (k = 0; k < fillHeight; k++)    //loop for last row
			{
				memset(output, 0, blockSize);
				output += blockSize;
			}

		}
	}
}


void merge(int blockSize, int width, int height, unsigned char *input, unsigned char *output, int *mv)
{
	int i, j, k;
	unsigned char *p_out;
	unsigned char *p_row;

	/*TODO:
	Computation of pixFillHeight and pixFillWidth needs fix!!

	Short example:

	height = 270
	270 % 8 == 6
	276 / 8 == 34.5 !!WRONG

	We need result 2, which is heightF==272 in this case

	This also does't solve the problem:
	int pixFillHeight = blockSize - height % blockSize;

	because if modulo == 0:

	pixFillHeight == 8


	*/

	int pixFillHeight = blockSize - (height%blockSize); //compute resting pixels filled in
	int pixFillWidth = blockSize  - (width%blockSize);


	int heightF = height + pixFillHeight;
	int widthF = width + pixFillWidth;
	int fillHeight = 0;
	int fillWidth = 0;

	for (i = 0; i < heightF / blockSize; i++)
	{
	    p_row = output + i*blockSize*width;

		for (j = 0; j < widthF / blockSize; j++)
		{
			p_out = p_row + j*blockSize;

			fillHeight = i == (height / blockSize) ? pixFillHeight : 0;
			fillWidth = j == (width / blockSize) ? pixFillWidth : 0;

			for (k = 0; k < blockSize - fillHeight; k++)
            {
				memcpy(p_out + k*width, input, blockSize - fillWidth);
				input += blockSize;
			}

		}
	}
}
