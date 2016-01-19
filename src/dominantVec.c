#include <string.h>
#include <stdlib.h>
#include "dominantVec.h"


int dominantVec(int numSubFram, float *input) {
    
    int startVal = 0 ;
    ResCon result = getCandiate (startVal ,input , numSubFrames);
    int numbofLoops = 1 ;
    int count = result.count ;
    int index = result.index ;
    
    while (numbofLoops < numSubFrames || count < numSubFrames/2){
        startVal++;
        result = getCandiate(startVal , input , numSubFrames);
        numbofLoops++ ;
        if(count < result.count){
            index = result.index ;
            count = result.count ;
        }
    }
    return index;
}


ResCon getCandidate(int start , float *input, int numSubFrames){
    int maj_index = start ;
    float border= (*input + start)/16 ;
    int count, count1 = 1 ;
    ResCon result ;
    for(i = start+1 ; i < numSubFram ; i++){
        if(*input + i <= *input + maj_index + border &&
        *input +maj_index - border <= *input+i){
            count ++ ;
            count1 ++ ;
        }
        else
        count -- ;
        if(count == 0){
            maj_index = i ;
            count = 1 ;
            count1 = 1 ;
            border= (*input + maj_index)/16;
        }
    }
    result.index = maj_index ;
    result.count = count1 ;
    return result ;
}
}
