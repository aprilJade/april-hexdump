#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include "../includes/dump_hex.h"

bool IsOverlapped(uchar* s1, uchar* s2)
{
	return memcmp(s1, s2, BUFFER_SIZE) == 0 ? true : false;
}

int DumpHexStdin(optvec* options)
{
	uchar readBuf[BUFFER_SIZE] = { 0, };
	uchar tmpBuf[BUFFER_SIZE] = { 0, };
	char tmp;
	int size = 0;
	int totalSize = 0;
	int ret = 0;
	bool b_isOverlapped = false;

	while ((ret = read(0, &tmp, 1)) >= 0)
	{
		if (ret == 0)
			break;
		readBuf[size] = tmp;
		size += ret;
		totalSize += ret;
		if (size < BUFFER_SIZE)
			continue;
		if (IsOverlapped(tmpBuf, readBuf) == true)
		{
			if (b_isOverlapped == false)
				write(1, "*\n", 2);
			b_isOverlapped = true;
			size = 0;
			continue;
		}
		PrintLine(options, readBuf, size, totalSize);
		memcpy(tmpBuf, readBuf, BUFFER_SIZE);
		size = 0;
		b_isOverlapped = false;
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
	int successCnt = 0;
	uchar buf[BUFFER_SIZE];

	// TODO: Implement feature - skip overlap
	for (int i = 0; i < fileCnt; i++)
	{
		if ((fd = open(files[i], O_RDONLY)) < 0)
		{
			ret = PrintError(files[i], procName);
			continue;
		}
		while ((readRet = read(fd, buf + size, BUFFER_SIZE - size)) >= 0)
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
		successCnt++;
	}
	if (successCnt == 0)
		ret = PrintFailAllArg(procName);
	else
	{
		PrintLine(options, buf, size, totalSize + (16 - size));
		PrintIndex(totalSize + 16);
		write(1, "\n", 1);
	}
	return ret;
}