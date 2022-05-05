/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:03:31 by seonggyk          #+#    #+#             */
/*   Updated: 2022/05/01 12:29:20 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dump_hex.h"
#include "../includes/hex_dump_tools.h"
#include "../includes/dump_hex_tools.h"
#include "../includes/dump_tools.h"
#include "../includes/file_cntl.h"
#include "../includes/str_cntl.h"
#include <unistd.h>
#include <stdlib.h>

void	last_print(char *buf, int size, int total_size, int flag)
{
	if (size > 0)
		print_remain_data(buf, total_size, flag);
	if (total_size > 0)
	{
		print_index_in_hex(total_size + BUFFER_SIZE, flag, 1);
		write(1, "\n", 1);
	}
}

int	dump_hex_dynamic(int flag)
{
	char	buffer[BUFFER_SIZE];
	char	temp;
	int		size;
	int		total_size;
	int		ret;

	total_size = 0;
	while (1)
	{
		size = 0;
		ret = 0;
		init_buffer(buffer);
		while (size != BUFFER_SIZE)
		{
			ret = read(0, &temp, 1);
			if (ret < 0)
				return (-1);
			charcat(buffer, temp);
			size += ret;
		}
		total_size += size;
		print_one_line(buffer, total_size, size, flag);
	}
	return (EXIT_FAILURE);
}

int	print_file_end_on(char buf[16], char *file, int *total_size, int size)
{
	int		ret;
	int		fd;
	int		is_overlap;
	char	tmp_buf[16];

	fd = file_open(file);
	is_overlap = 0;
	while (1)
	{
		ret = check_read_error(buf, file, size, fd);
		if (ret < 0)
			break ;
		size += ret;
		if (check_size_limit(fd, size) < 0)
			break ;
		*total_size += size;
		if (check_overlap(buf, tmp_buf, &size, &is_overlap) > 0)
			continue ;
		memory_copy(tmp_buf, buf);
		print_one_line(buf, *total_size, size, 1);
		size = 0;
		is_overlap = 0;
	}
	return (size);
}

int	print_file_end_off(char buf[16], char *file, int *total_size, int size)
{
	int		ret;
	int		fd;
	int		is_overlap;
	char	tmp_buf[16];

	is_overlap = 0;
	fd = file_open(file);
	while (1)
	{
		ret = check_read_error(buf, file, size, fd);
		if (ret < 0)
			break ;
		size += ret;
		if (check_size_limit(fd, size) < 0)
			break ;
		*total_size += size;
		if (check_overlap(buf, tmp_buf, &size, &is_overlap) > 0)
			continue ;
		memory_copy(tmp_buf, buf);
		print_one_line(buf, *total_size, size, 0);
		size = 0;
		is_overlap = 0;
	}
	return (size);
}

int	dump_hex(int argc, char **argv, int flag, char buf[BUFFER_SIZE])
{
	int		i;
	int		size;
	int		total_size;

	i = 1 + flag;
	total_size = 0;
	size = 0;
	while (i < argc)
	{
		if (check_file(argv[i], &i) == EXIT_FAILURE)
			continue ;
		if (flag)
			size = print_file_end_on(buf, argv[i], &total_size, size);
		else
			size = print_file_end_off(buf, argv[i], &total_size, size);
		i++;
	}
	total_size += size;
	last_print(buf, size, total_size, flag);
	if (total_size == 0 && argv[--i][0] != 0)
		ft_print_fd_error(argv[i]);
	return (EXIT_SUCCESS);
}
