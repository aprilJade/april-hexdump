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
#include "../includes/str_cntl.h"
#include <unistd.h>


void	charcat(char *dest, char c)
{
	while (*dest)
		dest++;
	*dest = c;
}

void	init_buffer(char *buffer)
{
	int		i;

	i = 0;
	while (i < 16)
		buffer[i++] = 0;
}

void	read_error(int fd, char *file_path)
{
	close(fd);
	ft_path_error(file_path);
	file_path[0] = 0;
}

void	print_remain_data(char *data, int size, int flag)
{
	print_index_in_hex(size + (16 - size % 16), flag, 0);
	print_data_in_hex((unsigned char *)data, size % 16, flag);
	if (flag)
		print_data_in_ascii((unsigned char *)data, size % 16);
}

void	print_one_line(char *data, int total_size, int size, int flag)
{
	print_index_in_hex(total_size, flag, 0);
	print_data_in_hex((unsigned char *)data, size, flag);
	if (flag)
		print_data_in_ascii((unsigned char *)data, size);
}


int	check_read_error(char buf[BUFFER_SIZE], char *file, int size, int fd)
{
	int	ret;

	ret = read(fd, buf + size, BUFFER_SIZE - size);
	if (ret < 0)
		read_error(fd, file);
	return (ret);
}

int	check_size_limit(int fd, int size)
{
	if (size != BUFFER_SIZE)
	{
		close(fd);
		return (-1);
	}
	return (1);
}

int	memory_compare(char s1[BUFFER_SIZE], char s2[BUFFER_SIZE])
{
	int	i;
	int	ret;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		ret = s1[i] - s2[i];
		if (ret != 0)
			return (-1);
		i++;
	}
	return (1);
}

void	memory_copy(char dest[BUFFER_SIZE], char src[BUFFER_SIZE])
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
}

int	check_overlap(char buf[16], char tmp[16], int *size, int *is_overlap)
{
	if (memory_compare(buf, tmp) == 1)
	{
		if (*is_overlap == 0)
		{
			*is_overlap = 1;
			write(1, "*\n", 2);
		}
		*size = 0;
		return (1);
	}
	return (-1);
}

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
