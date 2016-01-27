#ifndef SPLIT_MERGE_H
#define SPLIT_MERGE_H

#include "preesm.h"

typedef struct ResCon{
	   int count;
	   int index;
};
void dominantVec(int numSubFram , int *inputx , int *inputy , int *output) ;
ResCon getCandidate(int start , int *inputx, int *inputy, int numSubFrames) ;

#endif
