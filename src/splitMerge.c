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
	int pixFillHeight = 0 ; //compute resting pixels to be filled in, in order to make frame dividable by blockSize
	int pixFillWidth  = 0 ;

	pixFillHeight = blockSize - (height%blockSize);
	pixFillWidth  = blockSize - (width%blockSize) ;

	int heightF = height + pixFillHeight; //get filled size
	int widthF = width + pixFillWidth;
	int nbBlocksH = heightF/blockSize;
	int nbBlocksW = widthF/blockSize;

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

            memset(blockIndex + i*nbBlocksW +j, i*nbBlocksW + j, 1); //write block index to output

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
	unsigned char *p_in;

	int pixFillHeight = 0 ; //compute resting pixels to be filled in, in order to make frame dividable by blockSize
	int pixFillWidth  = 0 ;

	pixFillHeight = blockSize - (height%blockSize);
    pixFillWidth  = blockSize - (width%blockSize);

	int heightF = height + pixFillHeight;
	int widthF = width + pixFillWidth;

	int fillHeight = 0;
	int fillWidth = 0;

    int shiftX=mv[0]; // get vector values
    int shiftY=mv[1];
    int left = 0;
	for (i = 0; i < heightF / blockSize; i++)
	{
	    p_row = output + i*blockSize*width + shiftY*width;
		for (j = 0; j < widthF / blockSize; j++)
		{
			p_out = p_row + j*blockSize + shiftX;
			fillHeight = i == (height / blockSize) ? (pixFillHeight + shiftY) : 0;
			fillWidth = j == (width / blockSize) ? (pixFillWidth + shiftX): 0;

			for (k = 0; k < blockSize - fillHeight; k++)
            {
                //case for upper border
                if(p_out + k*width < output)
                 {
                    p_in += blockSize;
                    continue;
                 }
                 //case for left border
                else if (p_out + k*width < output + i*blockSize*width + k*width)
                {
                    memcpy(p_out + k*width, input + shiftX, blockSize);
                    p_in += blockSize;
                }
                //ordinal loop
                else{
                    memcpy(p_out + k*width, input, blockSize - fillWidth);
                    input += blockSize;
                }
                left=k; //store last k
			}
			input+=(blockSize-left-1)*blockSize; //fix input pointer position
		}
	}
}
