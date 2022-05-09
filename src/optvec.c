#include "../includes/optvec.h"

void initOptvec(optvec* vec)
{
    vec->size = 0;
    for (int i = 0; i < OPTION_COUNT; i++)
        vec->data[i] = 0;
}

int insert(uchar data, optvec* vec)
{
    if (vec->size == OPTION_COUNT)
        return (-1);
    vec->data[vec->size] = data;
    vec->size += 1;
    return (vec->size);
}

char getData(optvec* vec, int idx)
{
    if (idx < 0 || idx > OPTION_COUNT - 1)
        return (-1);
    return vec->data[idx];
}