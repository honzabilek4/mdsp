#ifndef DOM_VEC_H
#define DOM_VEC_H

#include "preesm.h"

typedef struct ResCon{
	   int count;
	   int index;
};
void dominantVec(int width, int height, int blockSize ,IN int *input_x , int *input_y ,OUT int *output);
ResCon getCandidate(int start , int *inputx, int *inputy, int numSubFrames) ;

#endif
