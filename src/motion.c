#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "motion.h"


// block comp return SAD of block
unsigned int SAD(unsigned char *ref, unsigned char *cur,int blockSize,int width){
    unsigned int res;
    int i, j;

	for (i = 0; i < blockSize; ++i)
	{
		for (j = 0; j < blockSize; ++j)
		{
			res += abs(cur[j + i*width] - ref[j + i*blockSize]);
		}
	}
	return res;
}

//full Search algorithm - comparing one actual block to the reference frame
void fullSearch(int width, int height, int blockSize,IN int *blockIndex,IN unsigned char *input,IN unsigned char *reference,OUT int *output_x,OUT int *output_y)
{
    int i,j;
    int sad,pre;
    int positon[2],mv[2];
    int nblockH = (height + blockSize - height%blockSize)/blockSize;
    int nblockW = (width + blockSize - width%blockSize)/blockSize;
    if(*reference == NULL)
        return;
    int currentIndex = *blockIndex;
    pre=sizeof(int);

            for(i=0;i<(height-blockSize);i++){
                for(j=0;j<(width-blockSize);j++){

                    sad=SAD(reference+j*blockSize+i*width,input,blockSize,width);
                    if (pre>sad){
                        pre=sad;
                        positon[0]=i;
                        positon[1]=j;// we get position of the best corresponding block
                    }
                }
            }
        mv[0]= (currentIndex*blockSize)%width-i;
        mv[1]= (currentIndex/nblockW)*blockSize-j;// calculate the movement vector


        memset(output_x+currentIndex,mv[0],1);
        memset(output_y+currentIndex,mv[1],1);


}


