/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_hex_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:44:01 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 22:29:47 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dump_hex_tools.h"
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
