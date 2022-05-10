#ifndef OPTVEC_H
#define OPTVEC_H
#include "../includes/general.h"
#define OPTION_COUNT    8

typedef struct optvec
{
    uchar data[OPTION_COUNT];
    int size;
} optvec;

void InitOptvec(optvec* vec);
int Insert(uchar data, optvec* vec);

#endif