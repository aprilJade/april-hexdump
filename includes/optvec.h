#ifndef OPTVEC_H
#define OPTVEC_H
#include "../includes/general.h"
#define OPTION_COUNT    8

typedef struct optvec
{
    uchar data[OPTION_COUNT];
    uint size;
} optvec;

void initOptvec(optvec* vec);
int insert(uchar data, optvec* vec);
char getData(optvec* vec, uint idx);

#endif