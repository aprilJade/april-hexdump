#ifndef OPTVEC_H
#define OPTVEC_H

#define OPTION_COUNT    8

typedef struct optvec
{
    void* data[OPTION_COUNT];
    int size;
} optvec;

void InitOptvec(optvec* vec);
int Insert(void (*fuction)(unsigned char*, int), optvec* vec);

#endif