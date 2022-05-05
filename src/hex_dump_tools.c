/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_dump_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:17:38 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 21:29:30 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hex_dump_tools.h"
#include <unistd.h>

void	print_number_in_hex(int number, char *hex)
{
	if (number > 15)
	{
		print_number_in_hex(number / 16, hex);
		write(1, &hex[number % 16], 1);
	}
	else
		write(1, &hex[number % 16], 1);
}

void	print_index_in_hex(int size, int flag, int last)
{
	int		i;
	int		tmp;
	char	*hex;

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
		print_number_in_hex(size, hex);
	if (last == 0)
		write(1, "  ", 1 + flag);
}

void	print_data_in_hex(unsigned char *data, int size, int flag)
{
	int		i;
	char	*hex;

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
		print_spaces(i);
	if (flag)
	{
		if (i < 8)
			write(1, " ", 1);
		write(1, "  ", 2);
	}
	else
		write(1, "\n", 1);
}

void	print_data_in_ascii(unsigned char *data, int size)
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

void	print_spaces(int len)
{
	int	i;

	i = 47 - len * 3;
	while (i-- > 0)
		write(1, " ", 1);
}
