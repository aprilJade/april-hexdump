#include "../includes/hex_dump_tools.h"
#include "../includes/error_msg.h"
#include <unistd.h>

void charcat(char *dest, char c)
{
	while (*dest)
		dest++;
	*dest = c;
}

void printLine(char *data, int total_size, int size, int flag)
{
	PrintIndexInHex(total_size, flag, 0);
	PrintDataInHex((uchar *)data, size, flag);
	if (flag)
		PrintDataInAscii((uchar *)data, size);
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

void PrintIndexInHex(int size, int flag, int last)
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
	write(1, "00000000", 7 - i + flag);
	if (size > 0)
		PrintIntinHex(size, hex);
	if (last == 0)
		write(1, "  ", 1 + flag);
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
