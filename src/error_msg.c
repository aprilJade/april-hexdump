#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include "../includes/error_msg.h"

void ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int printError(char *file_path)
{
	ft_putstr("ft_hexdump: ");
	ft_putstr(basename(file_path));
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putstr("\n");
	return (8);
}