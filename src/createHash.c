#include <string.h>
#include <stdlib.h>
#include "createHash.h"



unsigned long hash(unsigned char *data)
{
    unsigned long hash = 5381;
    int c;

    while (c = *data++)
        hash = hash xor *(data+c) ;
       
    return hash;
}
