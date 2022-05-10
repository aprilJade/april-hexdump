#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>
#include "../includes/error_msg.h"
#include "../includes/general.h"

void PrintString(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int PrintError(char *file_path, char* procName)
{
	PrintString(basename(procName));
	PrintString(": ");
	PrintString(basename(file_path));
	PrintString(": ");
	PrintString(strerror(errno));
	PrintString("\n");
	return EXIT_FAILURE;
}

int	PrintOptError(char opt, char* procName)
{
	PrintString(basename(procName));
	PrintString(": ");
	PrintString("invalid option -- \'");
	PrintString(&opt);
	PrintString("\'\n");
	return EXIT_FAILURE;
}

int PrintFailAllArg(char* procName)
{
	PrintString(basename(procName));
	PrintString(": ");
	PrintString("all input file arguments failed\n");
	return EXIT_FAILURE;
}