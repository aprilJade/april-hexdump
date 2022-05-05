#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/dump_hex.h"
#include "../includes/error_msg.h"

enum argvIndex
{
	programName,
	option
};

int CheckOption(int argc, char **argv)
{
	if (argc < 2)
		return (false);
	if (strcmp(argv[option], "-C") != 0)
		return (false);
	return (true);
}

int main(int argc, char **argv)
{
	int optFlag;

	if (argc > 0)
	{
		optFlag = CheckOption(argc, argv);
		if ((!optFlag && argc == 1) || (optFlag && argc == 2))
			return (DumpHexStdin(optFlag));
		else
			return (DumpHexFiles(argc, argv, optFlag));
	}
	return (8);
}
