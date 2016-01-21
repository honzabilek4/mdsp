#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "splitMerge.h"


//frame is divided into the blocks blockSize x blockSize
//direction is from the most left to the right block per row
//within each block pixels are copied per row
void split(int blockSize, int width, int height, unsigned char *input, unsigned char *output)
{

    int i, j, k;
    unsigned char *p_in = input;
    int fillHeight = height%blockSize; //compute resting pixels to be filled in, in order to make frame dividable by blockSize
    int fillWidth = width%blockSize;

    for (i = 0; i < (height + fillHeight) / blockSize; i++)
    {
        for (j = 0; j < (width + fillWidth) / blockSize; j++)
        {
            //other than last row
            if (i != height / blockSize)
            {
                //ordinal loop
                if (j != width / blockSize)
                {
                    for (k = 0; k < blockSize; k++)
                    {
                        memcpy(output, p_in + k*width, blockSize); //copy one block line to output
                        output += blockSize; //increment output pointer per one block line
                    }
                }
                //right border case
                else
                {
                    for (k = 0; k < blockSize; k++)
                    {
                        memcpy(output, p_in + k*width, blockSize - fillWidth); //copy the resting pixels on the right side
                        memset(output + (blockSize - fillWidth), 0, fillWidth); // fill the last block to size of blockSize
                        output += blockSize; //increment output pointer per one block line
                    }
                }
            }
            //bottom border case
            else
            {
                //ordinal loop on bottom border
                if (j != width / blockSize)
                {
                    for (k = 0; k < blockSize - fillWidth; k++)
                    {
                        memcpy(output, p_in + k*width, blockSize); //copy one block line to output
                        output += blockSize; //increment output pointer per one block line
                    }
                    for (k = 0; k < fillWidth; k++)
                    {
                        memset(output, 0, blockSize);
                    }
                }

                //last block (right and bottom border case)
                else
                {

                    for (k = 0; k < blockSize - fillHeight; k++)
                    {
                        memcpy(output, p_in + k*width, blockSize - fillWidth); //copy the resting pixels on the right side
                        memset(output + (blockSize - fillWidth), 0, fillWidth); // fill the last block to size of blockSize
                        output += blockSize; //increment output pointer per one block line
                    }
                    for (k = 0; k < fillHeight; k++)
                    {
                        memset(output, 0, blockSize);
                        output += blockSize;
                    }
                }
            }
            p_in += j*blockSize; // get start of the next block
        }
        p_in = input + i*blockSize*width;
    }
}


void merge(int blockSize, int width, int height, unsigned char *input, unsigned char *output)
{
    int i, j, k;
    unsigned char *p_out = output;
    int fillHeight = height%blockSize; //compute resting pixels filled in
    int fillWidth = width%blockSize;

    int	frameSize = (width + fillWidth)*(height + fillHeight);

    for (i = 0; i < (height + fillHeight) / blockSize; i++)
    {
        for (j = 0; j < (width + fillWidth) / blockSize; j++)
        {

            //TODO: this loop is wrong, k too big
            for (k = 0; k < blockSize; k++)
            {
                memcpy(p_out + k*(width + fillWidth), input, blockSize); //copy one block line to output
                input += blockSize; //increment output pointer per one block line
            }
        }
        p_out = output + j * blockSize;
    }
}
