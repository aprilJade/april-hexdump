#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include "../includes/error_msg.h"

void PrintString(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int PrintError(char *file_path, char* processName)
{
	PrintString(processName);
	PrintString(": ");
	PrintString(basename(file_path));
	PrintString(": ");
	PrintString(strerror(errno));
	PrintString("\n");
	return (8);
}

int	PrintOptError(char opt, char* processName)
{
	PrintString(basename(processName));
	PrintString(": ");
	PrintString("invalid option -- \'");
	PrintString(&opt);
	PrintString("\'\n");
	return (8);
}