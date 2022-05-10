#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void charcat(char *dest, char c)
{
	while (*dest)
		dest++;
	*dest = c;
}
/*
void printLine(char *data, int total_size, int size, int flag)
{
	PrintIndexInHex(total_size, flag, 0);
	PrintDataInHex((uchar *)data, size, flag);
	if (flag)
		PrintDataInAscii((uchar *)data, size);
}

void PrintDataInHex(uchar *data, int size, int flag)
{
	int i = 0;
	const char *hex = "0123456789abcdef";
	while (i++ < size)
	{
		write(1, &hex[*data / 16], 1);
		write(1, &hex[*data % 16], 1);
		if (flag)
		{
			if (i < 16)
				write(1, " ", 1);
			if (i == 8)
				write(1, " ", 1);
		}
		else
		{
			if (i % 2 == 0 && i < 16)
				write(1, " ", 1);
		}
		data++;
	}
	if (--i < 16)
		PrintSpaces(i, flag);
	if (flag)
	{
		if (i < 8)
			write(1, " ", 1);
		write(1, "  ", 2);
	}
	else
		write(1, "\n", 1);
}

void PrintDataInAscii(uchar *data, int size)
{
	write(1, "|", 1);
	while (size--)
	{
		if (*data < 32 || *data > 126)
			write(1, ".", 1);
		else
			write(1, data, 1);
		data++;
	}
	write(1, "|\n", 2);
}

void PrintSpaces(int len, int flag)
{
	int i = flag ? 47 - len * 3 : 39 - 5 * (len / 2);
	while (i-- > 0)
		write(1, " ", 1);
}
*/

bool isEscapeSequence(char c)
{
	if (c <= 0x0d && c >= 0x07)
		return (true);
	if (c == 0x1b || c == 0x22 || c == 0x27 || c == 0x3f || c == 0x57)
		return (true);
	return (false);
}

void PrintIntinHex(int number, const char *hex)
{
	if (number > 15)
	{
		PrintIntinHex(number / 16, hex);
		write(1, &hex[number % 16], 1);
	}
	else
		write(1, &hex[number % 16], 1);
}

void PrintOneByteInHex(char data)
{
	char* hex = "0123456789abcedf";
	write(1, &hex[data / 16], 1);
	write(1, &hex[data % 16], 1);
}

void PrintNumber(unsigned char n)
{
	unsigned char c;
	if (n > 9)
	{
		PrintNumber(n / 10);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
	else
	{
		c = n % 10 + '0';
		write(1, &c, 1);
	}
}

void PrintIndex(int size)
{
	int i = 0;
	int tmp;
	const char *hex = "0123456789abcdef";
	size -= 16;
	tmp = size;
	while (tmp > 0)
	{
		tmp /= 16;
		i++;
	}
	write(1, "00000000", 7 - i);
	if (size > 0)
		PrintIntinHex(size, hex);
}

void PrintNormal(char* data, int size, int totalSize)
{
	PrintIndex(totalSize);
	for (int i = 0; i < 16 && i < size; i += 2)
	{
		write(1, " ", 1);
		PrintOneByteInHex(*++data);
		PrintOneByteInHex(*--data);
		data += 2;
	}
	write(1, "\n", 1);
}

void PrintOneByteOctal(char* data, int size, int totalSize)
{
	PrintIndex(totalSize);
	for (int i = 0; i < size; i++)
	{
		write(1, " ", 1);
		PrintNumber((unsigned char)*data++);
	}
	write(1, "\n", 1);
}

void PrintOneByteChar(char* data, int size, int totalSize)
{
	PrintIndex(totalSize);
	for (int i = 0; i < size; i++)
	{
		if (isEscapeSequence(*data))
		{
			write(1, "   ", 2);
			switch (*data)
			{
				case '\t':
					write(1, "\\t", 2);
				case '\n':
					write(1, "\\n", 2);
				case '\r':
					write(1, "\\r", 2);
				case '\v':
					write(1, "\\v", 2);
			}
		}	
	}
}

void PrintCanonical(char* data, int size, int totalSize);
void PrintTwoBytesDecimal(char* data, int size, int totalSize);
void PrintTwoBytesOctal(char* data, int size, int totalSize);
void PrintTwoBytesHex(char* data, int size, int totalSize);
void PrintTotalSizeInHex(int totalSize);

void PrintLine(optvec* options, char* data, int size, int totalSize)
{
	//char c;
	//for (int i = 0; i < options->size; i++)
	//{
	//	switch (c = options->data[i])
	//	{
	//	case 'b':
	//		PrintOneByteOctal(data, size, totalSize);
	//		break;
	//	case 'c':
	//		PrintOneByteChar(data, size, totalSize);
	//		break;
	//	case 'C':
	//		PrintCanonical(data, size, totalSize);
	//		break;
	//	case 'd':
	//		PrintTwoBytesDecimal(data, size, totalSize);
	//		break;
	//	case 'o':
	//		PrintTwoBytesOctal(data, size, totalSize);
	//		break;
	//	case 'x':
	//		PrintTwoBytesHex(data, size, totalSize);
	//		break;
	//	default:
	//		break;
	//	}
	//}
	if (options->size == 0)
		PrintNormal(data, size, totalSize);
}