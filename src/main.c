#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include "../includes/dump_hex.h"
#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include "../includes/general.h"
#include "../includes/func_vec.h"

int main(int argc, char** argv)
{
	char c;
	funcVec* printFunctions = (funcVec*)malloc(sizeof(funcVec));
	InitFuncVec(printFunctions);
	static struct option longOptions[] =
	{
		{"one-byte-octal",		no_argument, 0, 'b'},
		{"one-byte-char",		no_argument, 0, 'c'},
		{"canonical",			no_argument, 0, 'C'},
		{"two-bytes-decimal",	no_argument, 0, 'd'},
		{"two-bytes-octal",		no_argument, 0, 'o'},
		{"two-bytes-hex",		no_argument, 0, 'x'},
		{0, 0, 0, 0} 
	};
	while ((c = getopt_long(argc, argv, "bcCdox", longOptions, 0)) > 0)
	{
		switch (c)
		{
		case 'b':
			Insert(PrintOneByteOctal, printFunctions);
			break;
		case 'c':
			Insert(PrintOneByteChar, printFunctions);
			break;
		case 'C':
			Insert(PrintCanonical, printFunctions);
			break;
		case 'd':
			Insert(PrintTwoBytesDecimal, printFunctions);
			break;
		case 'o':
			Insert(PrintTwoBytesOctal, printFunctions);
			break;
		case 'x':
			Insert(PrintTwoBytesHex, printFunctions);
			break;
		default:
			PrintOptError(c, argv[0]);
			free(printFunctions);
			return EXIT_FAILURE;
		}
	}
	
	int filesCnt = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			filesCnt++;
	}
	
	char** files;
	int idx = 0;
	if (filesCnt != 0)
	{
		files = (char**)malloc(sizeof(char*) * filesCnt);
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] != '-')
				files[idx++] = argv[i];
		}
	}
	
	int ret = 0;
	if (filesCnt == 0)
		ret = DumpHexStdin(printFunctions);
	else
		ret = DumpHexFiles(filesCnt, files, printFunctions, argv[0]);
	if (filesCnt != 0)
		free(files);
	free(printFunctions);
	return ret;
}
