#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"

#define INDEX_LEN 8
static const char* g_strBase = "0123456789abcdef";
static char g_nbrBuf[7];

enum e_base
{
	OCTAL = 8,
	DECIMAL = 10,
	HEXADECIMAL = 16
};

void PrintOneByteInHex(uchar data)
{
	write(1, &g_strBase[data / HEXADECIMAL], 1);
	write(1, &g_strBase[data % HEXADECIMAL], 1);
}

void PrintCharInOctal(uchar n)
{
	char buf[4];
	int i;

	for (i = 0; i < 3; i++)
		buf[i] = '0';
	buf[i--] = 0;
	while (n > 0)
	{
		buf[i--] = (n % 8) + '0';
		n /= 8;
	}
	write(1, buf, 3);
}

void PrintIndex(int size)
{
	int i = 0;
	char buf[INDEX_LEN];
	for (i = 0; i < INDEX_LEN; i++)
		buf[i] = '0';
	
	size -= BUFFER_SIZE;
	while (size > 0)
	{
		buf[--i] = g_strBase[size % HEXADECIMAL];
		size /= 16;
	}
	write(1, buf, INDEX_LEN);
}

void PrintShortToBase(ushort n, int base)
{
	int digit;
	int i;
	
	if (base == OCTAL)
		digit = 6;
	else if (base == DECIMAL)
		digit = 5;
	else if (base == HEXADECIMAL)
		digit = 4;

	for (i = 0; i < digit; i++)
		g_nbrBuf[i] = '0';
	g_nbrBuf[i--] = 0;
	while (n > 0)
	{
		g_nbrBuf[i--] = g_strBase[n % base];
		n /= base;
	}
	write(1, g_nbrBuf, digit);
}

void PrintNormal(uchar* data, int size)
{
	ushort tmp;
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, " ", 1);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, HEXADECIMAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}


void PrintOneByteOctal(uchar* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		write(1, " ", 1);
		PrintCharInOctal(*data++);
	}
	write(1, "\n", 1);
}

bool isPrintable(uchar c)
{
	if (c < 32 || c > 126)
		return false;
	return true;
}

void PrintOneByteChar(uchar* data, int size)
{
	char buf[6][3] = {"\\0", "\\t", "\\n", "\\v", "\\f", "\\r"};
	uchar tmp;
	for (int i = 0; i < size; i++)
	{
		if (isPrintable(*data))
		{
			write(1, "   ", 3);
			write(1, data, 1);
		}
		else
		{
			if ((*data >= 9 && *data <= 13) || *data == 0)
			{
				write(1, "  ", 2);
				write(1, &buf[*data % 8], 2);
			}
			else 
			{
				write(1, " ", 1);
				tmp = *data;
				int digit = 0;
				while (tmp > 0)
				{
					digit++;
					tmp /= 10;
				}
				write(1, "000", 3 - digit);
				PrintCharInOctal(*data);
			}
		}
		data++;
	}
	write(1, "\n", 1);
}

void PrintCanonical(uchar* data, int size)
{
	write(1, " ", 1);
	for (int i = 0; i < size; i++)
	{
		if (i == 8)
			write(1, " ", 1);
		write(1, " ", 1);
		PrintOneByteInHex(data[i]);
	}
	// TODO: refactor hard coding
	int remainCnt = 48 - size * 3 + (size < 9 ? 1 : 0);
	write(1, "                                                 ", remainCnt);
	write(1, "  |", 3);
	for (int i = 0; i < size; i++)
	{
		if (isPrintable(*data))
			write(1, data, 1);
		else
			write(1, ".", 1);
		data++;
	}
	write(1, "|\n", 2);
}

void PrintTwoBytesDecimal(uchar* data, int size)
{
	ushort tmp;
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, "   ", 3);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, DECIMAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}

void PrintTwoBytesOctal(uchar* data, int size)
{
	ushort tmp;
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, "  ", 2);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, OCTAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}

void PrintTwoBytesHex(uchar* data, int size)
{
	ushort tmp;
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, "    ", 4);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, HEXADECIMAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}

void PrintLine(optvec* options, uchar* data, int size, int totalSize)
{
	for (int i = 0; i < options->size; i++)
	{
		PrintIndex(totalSize);
		switch (options->data[i])
		{
		case 'b':
			PrintOneByteOctal(data, size);
			break;
		case 'c':
			PrintOneByteChar(data, size);
			break;
		case 'C':
			PrintCanonical(data, size);
			break;
		case 'd':
			PrintTwoBytesDecimal(data, size);
			break;
		case 'o':
			PrintTwoBytesOctal(data, size);
			break;
		case 'x':
			PrintTwoBytesHex(data, size);
			break;
		default:
			break;
		}
	}

	if (options->size == 0)
	{
		PrintIndex(totalSize);
		PrintNormal(data, size);
	}
}