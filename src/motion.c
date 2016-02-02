#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "motion.h"
#include <limits.h>
#include <stdio.h>


// block comp return SAD of block
unsigned long SAD(unsigned char *ref, unsigned char *cur,int blockSize,int width){
    unsigned long res = 0;
    int i, j;

	for (i = 0; i < blockSize; ++i)
	{
		for (j = 0; j < blockSize; ++j)
		{
			res += abs(cur[j + i*blockSize] - ref[j + i*width]);
			//printf("RES: %lu \n",res);
		}
	}
	return res;
}

//full Search algorithm - comparing one actual block to the reference frame
void fullSearch(int width, int height, int blockSize,IN int *blockIndex,IN unsigned char *input,IN unsigned char *reference,OUT int *output_x,OUT int *output_y)
{
    int i,j;
    unsigned long sad;
    unsigned long pre = ULONG_MAX;
    int position[2]={0,0};
    int mv[2]={0,0};
    int nblockH = (height + blockSize - height%blockSize)/blockSize;
    int nblockW = (width + blockSize - width%blockSize)/blockSize;
    int currentIndex = *blockIndex;

    // should apply only to first frame with no reference on input
   if(*reference == '\0' || reference == NULL)
        {
          memset(output_x,0,1);
          memset(output_y,0,1);
          return;
        }

    //search only neighbour area  - set loop variables
   int iMax,jMax;
   int search = 3*blockSize;

   iMax = (currentIndex/nblockW)*blockSize + search;
   jMax = (currentIndex%nblockW)*blockSize + search;
   i = (currentIndex/nblockW)*blockSize - search;
   j = (currentIndex%nblockW)*blockSize - search;

   i= i<0 ? 0 : i;
   j= j<0 ? 0 : j;

   iMax = iMax>(height-blockSize)? (height - blockSize):iMax;
   jMax = jMax>(width-blockSize)? (width - blockSize):jMax;


   //start loop
   for(i;i<iMax;i++){
           for(j;j<jMax;j++){
               sad = SAD(reference+j+i*width,input,blockSize,width);

               if (pre>sad){
                        pre=sad;
                        position[0]=j;
                        position[1]=i;// we get position of the best corresponding block
                    }
            }
    }
     mv[0]=(currentIndex%nblockW)*blockSize - (position[0]);
     mv[1]=(currentIndex/nblockW)*blockSize - (position[1]);// calculate the movement vector, integer division

//
//     memset(output_x+currentIndex,mv[0],1);
//     memset(output_y+currentIndex,mv[1],1);

     *output_x = mv[0];
     *output_y = mv[1];

    //printf("PRE: %lu \n", pre);
    //printf("pos_x: %d \t pos_y: %d \n", position[0],position[1]);
      //printf("index: %d \t x: %d \t y: %d \n", currentIndex, mv[0], mv[1]);

     return;
}


