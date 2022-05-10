#include "../includes/optvec.h"

void InitOptvec(optvec* vec)
{
    vec->size = 0;
    for (int i = 0; i < OPTION_COUNT; i++)
        vec->data[i] = 0;
}

int Insert(void (*fuction)(unsigned char*, int), optvec* vec)
{
    vec->data[vec->size] = fuction;
    vec->size += 1;
    return vec->size;
}