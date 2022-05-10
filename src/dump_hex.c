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
		PrintLine(options, (uchar*)readBuf, size, totalSize + (16 - size));
		PrintIndex(totalSize + 16);
		write(1, "\n", 1);
		return EXIT_SUCCESS;
	}
}