#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include "../includes/dump_hex.h"

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
		PrintLine(options, readBuf, size, totalSize + (16 - size));
		PrintIndex(totalSize + 16);
		write(1, "\n", 1);
		return EXIT_SUCCESS;
	}
}

int DumpHexFiles(int fileCnt, char** files, optvec* options, char* procName)
{
	int fd = 0;
	int ret = EXIT_SUCCESS;
	int readRet = 0;
	int size = 0;
	int totalSize = 0;
	uchar buf[BUFFER_SIZE];

	for (int i = 0; i < fileCnt; i++)
	{
		if ((fd = open(files[i], O_RDONLY)) < 0)
		{
			ret = PrintError(files[i], procName);
			continue;
		}
		while ((readRet = read(fd, buf, BUFFER_SIZE)) >= 0)
		{
			if (readRet == 0)
				break;
			size += readRet;
			totalSize += readRet;
			if (size < 16)
				continue;
			PrintLine(options, buf, size, totalSize);
			size = 0;
			for (int i = 0; i < BUFFER_SIZE; i++)
				buf[i] = 0;
		}
		if (readRet == FAIL_TO_READ)
			ret = PrintError(files[i], procName);
	}
	if (readRet == -1)
		ret = EXIT_FAILURE;
	else
	{
		PrintLine(options, buf, size, totalSize + (16 - size));
		PrintIndex(totalSize + 16);
		write(1, "\n", 1);
	}
	return ret;
}