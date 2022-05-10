#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"

static const char* g_strBase = "0123456789abcdef";
static char g_nbrBuf[7];

enum e_base
{
	OCTAL = 8,
	DECIMAL = 10,
	HEXA_DECIMAL = 16
};

void PrintIntinHex(int number)
{
	// TODO: remove recursive
	if (number > 15)
	{
		PrintIntinHex(number / HEXA_DECIMAL);
		write(1, &g_strBase[number % HEXA_DECIMAL], 1);
	}
	else
		write(1, &g_strBase[number % HEXA_DECIMAL], 1);
}

void PrintOneByteInHex(uchar data)
{
	write(1, &g_strBase[data / HEXA_DECIMAL], 1);
	write(1, &g_strBase[data % HEXA_DECIMAL], 1);
}

void PrintIndex(int size)
{
	int i = 0;
	int tmp;
	size -= BUFFER_SIZE;
	tmp = size;
	while (tmp > 0)
	{
		tmp /= BUFFER_SIZE;
		i++;
	}
	write(1, "00000000", 7 - i);
	if (size > 0)
		PrintIntinHex(size);
}

void PrintNormal(uchar* data, int size, int totalSize)
{
	PrintIndex(totalSize);
	for (int i = 0; i < BUFFER_SIZE && i < size; i += 2)
	{
		write(1, " ", 1);
		PrintOneByteInHex(*++data);
		PrintOneByteInHex(*--data);
		data += 2;
	}
	write(1, "\n", 1);
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

void PrintOneByteOctal(uchar* data, int size, int totalSize)
{
	PrintIndex(totalSize);
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

void PrintOneByteChar(uchar* data, int size, int totalSize)
{
	PrintIndex(totalSize);
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

void PrintCanonical(uchar* data, int size, int totalSize)
{
	PrintIndex(totalSize);
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

void PrintShortToBase(ushort n, int base)
{
	int digit;
	int i;

	if (base == OCTAL)
		digit = 6;
	else if (base == DECIMAL)
		digit = 5;
	else if (base == HEXA_DECIMAL)
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

void PrintTwoBytesDecimal(uchar* data, int size, int totalSize)
{
	ushort tmp;
	PrintIndex(totalSize);
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, "   ", 3);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, DECIMAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}

void PrintTwoBytesOctal(uchar* data, int size, int totalSize)
{
	ushort tmp;
	PrintIndex(totalSize);
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, "  ", 2);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, OCTAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}

void PrintTwoBytesHex(uchar* data, int size, int totalSize)
{
	ushort tmp;
	PrintIndex(totalSize);
	for (int i = 0; i < size; i += sizeof(short))
	{
		write(1, "    ", 4);
		memcpy(&tmp, data, sizeof(short));
		PrintShortToBase(tmp, HEXA_DECIMAL);
		data += sizeof(short);
	}
	write(1, "\n", 1);
}

void PrintLine(optvec* options, uchar* data, int size, int totalSize)
{
	char c;
	for (int i = 0; i < options->size; i++)
	{
		switch (c = options->data[i])
		{
		case 'b':
			PrintOneByteOctal(data, size, totalSize);
			break;
		case 'c':
			PrintOneByteChar(data, size, totalSize);
			break;
		case 'C':
			PrintCanonical(data, size, totalSize);
			break;
		case 'd':
			PrintTwoBytesDecimal(data, size, totalSize);
			break;
		case 'o':
			PrintTwoBytesOctal(data, size, totalSize);
			break;
		case 'x':
			PrintTwoBytesHex(data, size, totalSize);
			break;
		default:
			break;
		}
	}
	if (options->size == 0)
		PrintNormal(data, size, totalSize);
}