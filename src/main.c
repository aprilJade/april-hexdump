#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
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
	
	while ((c = getopt(argc, argv, "bcCdox")) > 0)
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
