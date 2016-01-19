#ifndef SPLIT_MERGE_H
#define SPLIT_MERGE_H

#include "preesm.h"

typedef struct ResCon{
	   int count;
	   int index;
};
int dominantVec(int numSubFram, float *input);
ResCon getCandidate(int start , float *input, int numSubFrames);

#endif