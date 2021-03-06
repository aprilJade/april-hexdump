#include "../includes/func_vec.h"

void InitFuncVec(funcVec* vec)
{
    vec->size = 0;
    for (int i = 0; i < OPTION_COUNT; i++)
        vec->data[i] = 0;
    vec->skipOffset = 0;
    vec->lenOffset = 0;
}

int Insert(void (*fuction)(unsigned char*, int), funcVec* vec)
{
    vec->data[vec->size] = fuction;
    vec->size += 1;
    return vec->size;
}