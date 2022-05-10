#ifndef HEX_DUMP_TOOLS_H
#define HEX_DUMP_TOOLS_H
#include "../includes/general.h"
#include "../includes/optvec.h"

void PrintIndex(int size);
void PrintLine(optvec* options, uchar* data, int size, int totalSize);

#endif
