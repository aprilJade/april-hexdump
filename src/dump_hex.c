#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

void PrintRemainLine(char *buf, int size, int totalSize, int flag)
{
	if (size > 0)
		PrintRemainData(buf, totalSize, flag);
	if (totalSize > 0)
	{
		PrintIndexInHex(totalSize + BUFFER_SIZE, flag, 1);
		write(1, "\n", 1);
	}
}
int DumpHexStdin(int flag)
{
	char buffer[BUFFER_SIZE];
	char temp;
	int size;
	int totalSize;
	int ret;

	totalSize = 0;
	while (1)
	{
		size = 0;
		ret = 0;
		memset(buffer, 0, BUFFER_SIZE);
		while (size != BUFFER_SIZE)
		{
			ret = read(0, &temp, 1);
			if (ret < 0)
				return (-1);
			charcat(buffer, temp);
			size += ret;
		}
		totalSize += size;
		printLine(buffer, totalSize, size, flag);
	}
	return (EXIT_FAILURE);
}

int DumpHexFiles(int argc, char **argv, int flag)
{
	int fd;
	int ret;
	int size = 0;
	int totalSize = 0;
	bool isOverlapped = false;
	char tmpBuf[BUFFER_SIZE];
	char readBuf[BUFFER_SIZE];

	for (int i = flag + 1; i < argc; i++)
	{
		if ((fd = open(argv[i], O_RDONLY)) < 0)
		{
			printError(argv[i]);
			continue;
		}

		while ((ret = read(fd, readBuf + size, BUFFER_SIZE - size)) > 0)
		{
			size += ret;
			if (size < BUFFER_SIZE)
				break;
			totalSize += size;
			if ((memcmp(tmpBuf, readBuf, BUFFER_SIZE) == 0))
			{
				if (!isOverlapped)
				{
					isOverlapped = true;
					write(1, "*\n", 2);
				}
				size = 0;
				continue;
			}
			memcpy(tmpBuf, readBuf, BUFFER_SIZE);
			printLine(readBuf, totalSize, size, flag);
			size = 0;
			isOverlapped = false;
		}
		if (ret < 0)
			printError(argv[i]);
		close(fd);
	}
	totalSize += size;
	if (totalSize == 0)
		return (EXIT_FAILURE);
	PrintRemainLine(readBuf, size, totalSize, flag);
	return (EXIT_SUCCESS);
}
