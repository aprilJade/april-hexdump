#ifndef DUMP_HEX_H
#define DUMP_HEX_H
#include "../includes/optvec.h"

int DumpHexStdin(optvec* options);
int DumpHexFiles(int fileCnt, char** files, optvec* options, char* procName);

#endif
