#include <string.h>
#include <stdlib.h>
#include "dominantVec.h"


void dominantVec(int width, int height, int blockSize ,IN int *input_x , int *input_y ,OUT int *output) {

    int numSubFrames = ((width + blockSize - width%blockSize)/blockSize)*
                       ((height + blockSize - height%blockSize)/blockSize);

    int startVal = 0 ;
    ResCon result = getCandidate (startVal ,input_x ,input_y , numSubFrames);
    int numbofLoops = 1 ;
    int count = result.count ;
    int index = result.index ;

    while (numbofLoops < numSubFrames && count < numSubFrames/3){
        startVal++;
        result = getCandidate(startVal ,input_x ,input_y , numSubFrames);
        numbofLoops++ ;
        if(count < result.count){
            index = result.index ;
            count = result.count ;
        }
    }
	memset(output, *(input_x+result.index) , 1);
	output ++;
	memset(output, *(input_y+result.index) , 1);
    ///return index;
}


ResCon getCandidate(int start , int *inputx, int *inputy, int numSubFrames){
    int i;
    int maj_index = start ;
    float borderx = *(inputx + start)/16 ;
    float bordery = *(inputy + start)/16 ;
    int count, count1 = 1 ;
    ResCon result ;
    for(i = start+1 ; i < numSubFrames ; i++){
        if(*(inputx + i) <= *(inputx + maj_index) + borderx &&
           *(inputx +maj_index) - borderx <= *(inputx+i) &&
	   *(inputy + i) <= *(inputy + maj_index) + bordery &&
           *(inputy +maj_index) - bordery <= *(inputy+i)){
            count ++ ;
            count1 ++ ;
        }
        else
        count -- ;
        if(count == 0){
            maj_index = i ;
            count = 1 ;
            count1 = 1 ;
            borderx= *(inputx + maj_index)/16;
            bordery= *(inputy + maj_index)/16;
        }
    }
    result.index = maj_index ;
    result.count = count1 ;
    return result ;
}
