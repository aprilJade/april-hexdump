#ifndef HEX_DUMP_TOOLS_H
#define HEX_DUMP_TOOLS_H
#include "../includes/general.h"

void printLine(char *data, int total_size, int size, int flag);
void PrintIndexInHex(int size, int flag, int last);
void PrintDataInHex(uchar *data, int size, int flag);
void PrintDataInAscii(uchar *data, int size);
void PrintRemainData(char *data, int size, int flag);
void charcat(char *dest, char c);
void PrintSpaces(int len, int flag);
void PrintIntinHex(int number, const char *hex);

void PrintNormal();
void PrintOneByteOctal();
void PrintOneByteChar();
void PrintCanonical();
void PrintTwoBytesDecimal();
void PrintTwoBytesOctal();
void PrintTwoBytesHex();
void PrintTotalSizeInHex();

#endif
