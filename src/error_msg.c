#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include "../includes/error_msg.h"
#include "../includes/general.h"

void printString(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int printError(char *file_path)
{
	printString(basename(g_procName));
	printString(": ");
	printString(basename(file_path));
	printString(": ");
	printString(strerror(errno));
	printString("\n");
	return (8);
}

int	printError(char c)
{
	printString(basename(g_procName));
	printString(": ");
	printString("invalid option -- \'");
	printString(&c);
	printString("\'\n");
}