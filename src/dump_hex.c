#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include "../includes/dump_hex.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

int DumpHexStdin(optvec* options)
{
	uchar readBuf[BUFFER_SIZE] = { 0, };
	char tmp;
	int size = 0;
	int totalSize = 0;
	int ret = 0;
	
	while ((ret = read(0, &tmp, 1)) >= 0)
	{
		if (ret == 0)
			break;
		readBuf[size] = tmp;
		size += ret;
		totalSize += ret;
		if (size < 16)
			continue;
		PrintLine(options, readBuf, size, totalSize);
		size = 0;
		for (int i = 0; i < BUFFER_SIZE; i++)
			readBuf[i] = 0;
	}

	if (ret == -1)
		return EXIT_FAILURE;
	else
	{
		PrintLine(options, (uchar*)readBuf, size, totalSize + (16 - size));
		PrintIndex(totalSize + 16);
		write(1, "\n", 1);
		return EXIT_SUCCESS;
	}
}

	/*
int DumpHexFiles(int argc, char** argv, optvec* options)
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
			PrintError(argv[i]);
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
			PrintError(argv[i]);
		close(fd);
	}
	totalSize += size;
	if (totalSize == 0)
		return (EXIT_FAILURE);
	if (size > 0)
		printLine(readBuf, totalSize + (BUFFER_SIZE - size), size, flag);
	PrintIndexInHex(totalSize + BUFFER_SIZE, flag, 1);
	write(1, "\n", 1);
	return (EXIT_SUCCESS);
}

	*/