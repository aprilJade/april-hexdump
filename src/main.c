#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../includes/dump_hex.h"
#include "../includes/error_msg.h"
#include "../includes/general.h"
#include "../includes/optvec.h"

int main(int argc, char** argv)
{
	char c;
	
	optvec* options = (optvec*)malloc(sizeof(optvec));
	initOptvec(options);
	
	while ((c = getopt(argc, argv, "bcCdox")) > 0)
	{
		if (c == 'b' || c == 'c' || c == 'C' || c == 'd' || c == 'o' || c == 'x')
			insert(c, options);
		else
		{
			PrintOptError(c, argv[0]);
			free(options);
			return (EXIT_FAILURE);
		}
	}
	
	int filesCnt = 0;
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
			filesCnt++;
	}
	
	if (filesCnt != 0)
	{
		write(1, "Sorry!! not implement yet hexdump for file input\n", 49);
		write(1, "Please use april hexdump with stdin only\n", 41);
		free(options);
		return (EXIT_FAILURE);
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
		ret = DumpHexStdin(options);
	//else
	//	ret = DumpHexFiles(filesCnt, files, options);
	if (filesCnt != 0)
		free(files);
	free(options);
	return (ret);
}
