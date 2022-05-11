#ifndef DUMP_HEX_H
#define DUMP_HEX_H
#include "../includes/func_vec.h"

int DumpHexStdin(funcVec* options);
int DumpHexFiles(int fileCnt, char** files, funcVec* options, char* procName);

#endif
