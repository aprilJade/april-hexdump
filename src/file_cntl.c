#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../includes/file_cntl.h"
#include "../includes/error_msg.h"

int file_open(char *file_path)
{
	int fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int get_file_size(char *file_path)
{
	int size;
	int ret;
	char buf[1 << 28];
	int fd;

	fd = file_open(file_path);
	if (fd < 0)
		return (-1);
	ret = -1;
	size = 0;
	while (ret != 0)
	{
		ret = read(fd, buf, 1 << 28);
		if (ret != -1)
			size += ret;
		else if (ret == -1)
			return (-1);
	}
	close(fd);
	return (size);
}

int dup_file(char *file_path, int size, char **data)
{
	char *ret;
	int fd;
	int var;

	ret = (char *)malloc(sizeof(char) * size);
	if (ret == 0)
		return (-1);
	fd = file_open(file_path);
	if (fd < 0)
		return (-1);
	var = read(fd, ret, size);
	if (var < 0)
	{
		free(ret);
		return (-1);
	}
	*data = ret;
	return (1);
}

int check_file(char *file, int *i)
{
	int fd;

	fd = file_open(file);
	if (fd < 0)
	{
		printError(file);
		*i += 1;
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
