#ifndef HEX_DUMP_TOOLS_H
#define HEX_DUMP_TOOLS_H
#include "../includes/general.h"
#include "../includes/optvec.h"

void PrintIndex(int size);
void PrintLine(optvec* options, uchar* data, int size, int totalSize);

void PrintOneByteOctal(uchar* data, int size);
void PrintOneByteChar(uchar* data, int size);
void PrintCanonical(uchar* data, int size);
void PrintTwoBytesDecimal(uchar* data, int size);
void PrintTwoBytesOctal(uchar* data, int size);
void PrintTwoBytesHex(uchar* data, int size);

#endif
