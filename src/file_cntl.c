#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../includes/error_msg.h"

int file_open(char *file_path)
{
	int fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}
