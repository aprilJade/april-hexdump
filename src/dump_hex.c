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
	return memcmp(s1, s2, BUFFER_SIZE) == 0;
}

int DumpHexStdin(funcVec* functions)
{
	uchar readBuf[BUFFER_SIZE] = { 0, };
	uchar tmpBuf[BUFFER_SIZE] = { 0, };
	int size = 0;
	int totalSize = 0;
	int ret = 0;
	bool b_isOverlapped = false;

	if (functions->skipOffset != 0)
	{
		//	Todo: Implement print error
		return EXIT_FAILURE;
	}

	while ((ret = read(0, readBuf + size, BUFFER_SIZE - size)) >= 0)
	{
		if (ret == 0 || (functions->lenOffset != 0 && totalSize > functions->lenOffset))
			break;
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
		PrintLine(functions, readBuf, size, totalSize);
		memcpy(tmpBuf, readBuf, BUFFER_SIZE);
		size = 0;
		b_isOverlapped = false;
		for (int i = 0; i < BUFFER_SIZE; i++)
		{
			readBuf[i] = 0;
			tmpBuf[i] = 0;
		}
	}

	if (functions->lenOffset > 0)
		totalSize = functions->lenOffset;

	if (ret == FAIL_TO_READ)
		return EXIT_FAILURE;
	else
	{
		PrintLine(functions, readBuf, size, totalSize + (16 - size));
		PrintIndex(totalSize + 16);
		write(1, "\n", 1);
		return EXIT_SUCCESS;
	}
}

int DumpHexFiles(int fileCnt, char** files, funcVec* functions, char* procName)
{
	int fd = 0;
	int ret = EXIT_SUCCESS;
	int readRet = 0;
	int size = 0;
	int totalSize = 0;
	int successCnt = 0;
	bool b_isOverlapped = false;
	uchar buf[BUFFER_SIZE];
	uchar tmpBuf[BUFFER_SIZE] = { 0, };

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
			if (size < BUFFER_SIZE)
				continue;
			if (IsOverlapped(tmpBuf, buf) == true)
			{
				if (b_isOverlapped == false)
					write(1, "*\n", 2);
				b_isOverlapped = true;
				size = 0;
				continue;
			}
			PrintLine(functions, buf, size, totalSize);
			memcpy(tmpBuf, buf, BUFFER_SIZE);
			size = 0;
			b_isOverlapped = false;
			for (int i = 0; i < BUFFER_SIZE; i++)
				buf[i] = 0;
		}

		if (readRet == FAIL_TO_READ)
			ret = PrintError(files[i], procName);
		successCnt++;
	}

	if (successCnt == 0)
		return PrintFailAllArg(procName);

	if (size != 0)
		PrintLine(functions, buf, size, totalSize + (16 - size));
	PrintIndex(totalSize + 16);
	write(1, "\n", 1);

	return ret;
}