#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/dump_hex.h"
#include "../includes/error_msg.h"

#define AH_OPT_OB_OCTAL		0b00100000
#define AH_OPT_OB_CHAR		0b00010000
#define AH_OPT_CANON		0b00001000
#define AH_OPT_TB_DECIMAL	0b00000100
#define AH_OPT_TB_OCTAL		0b00000010
#define AH_OPT_TB_HEX		0b00000001

int main(int argc, char** argv)
{
	unsigned char optFlag = 0;
	char c;
	while ((c = getopt(argc, argv, "bcCdox")) > 0)
	{
		switch (c)
		{
			case 'b':
				optFlag |= AH_OPT_OB_OCTAL;
				break;
			case 'c':
				optFlag |= AH_OPT_OB_CHAR;
				break;
			case 'C':
				optFlag |= AH_OPT_CANON;
				break;
			case 'd':
				optFlag |= AH_OPT_TB_DECIMAL;
				break;
			case 'o':
				optFlag |= AH_OPT_TB_OCTAL;
				break;
			case 'x':
				optFlag |= AH_OPT_TB_HEX;
				break;
			default:
				// TODO: implement print invaid option
				return (8);
		}
	}
	int filesCnt = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			filesCnt++;
	}
	char** files;
	if (filesCnt != 0)
	{
		files = (char**)malloc(sizeof(char*) * filesCnt);
		for (int i = 1; i < argc; i++)
			*files++ = argv[i];
		*files -= filesCnt;
	}
	int ret = 0;
	if (filesCnt == 0)
		ret = DumpHexStdin(optFlag);
	else
		ret = DumpHexFiles(filesCnt, files, optFlag);
	if (filesCnt != 0)
		free(files);
	return (ret);
}
