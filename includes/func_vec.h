#ifndef FUNC_VEC_H
#define FUNC_VEC_H

#define OPTION_COUNT    8

typedef struct funcVec
{
    void* data[OPTION_COUNT];
    int size;
} funcVec;

void InitOptvec(funcVec* vec);
int Insert(void (*fuction)(unsigned char*, int), funcVec* vec);

#endif