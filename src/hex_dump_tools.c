#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include <unistd.h>

void charcat(char *dest, char c)
{
	while (*dest)
		dest++;
	*dest = c;
}

void PrintRemainData(char *data, int size, int flag)
{
	PrintIndexInHex(size + (16 - size % 16), flag, 0);
	PrintDataInHex((unsigned char *)data, size % 16, flag);
	if (flag)
		PrintDataInAscii((unsigned char *)data, size % 16);
}

void printLine(char *data, int total_size, int size, int flag)
{
	PrintIndexInHex(total_size, flag, 0);
	PrintDataInHex((unsigned char *)data, size, flag);
	if (flag)
		PrintDataInAscii((unsigned char *)data, size);
}

void PrintIntinHex(int number, char *hex)
{
	if (number > 15)
	{
		PrintIntinHex(number / 16, hex);
		write(1, &hex[number % 16], 1);
	}
	else
		write(1, &hex[number % 16], 1);
}

void PrintIndexInHex(int size, int flag, int last)
{
	int i;
	int tmp;
	char *hex;

	hex = "0123456789abcdef";
	i = 0;
	size -= 16;
	tmp = size;
	while (tmp > 0)
	{
		tmp /= 16;
		i++;
	}
	write(1, "00000000", 7 - i + flag);
	if (size > 0)
		PrintIntinHex(size, hex);
	if (last == 0)
		write(1, "  ", 1 + flag);
}

void PrintDataInHex(unsigned char *data, int size, int flag)
{
	int i;
	char *hex;

	hex = "0123456789abcdef";
	i = 0;
	while (i++ < size)
	{
		write(1, &hex[*data / 16], 1);
		write(1, &hex[*data % 16], 1);
		if (i < 16)
			write(1, " ", 1);
		if (i == 8 && flag)
			write(1, " ", 1);
		data++;
	}
	if (--i < 16)
		PrintSpaces(i);
	if (flag)
	{
		if (i < 8)
			write(1, " ", 1);
		write(1, "  ", 2);
	}
	else
		write(1, "\n", 1);
}

void PrintDataInAscii(unsigned char *data, int size)
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

void PrintSpaces(int len)
{
	int i;

	i = 47 - len * 3;
	while (i-- > 0)
		write(1, " ", 1);
}
