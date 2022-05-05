/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 13:53:48 by seonggyk          #+#    #+#             */
/*   Updated: 2022/05/01 13:55:48 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dump_hex_tools.h"
#include "../includes/dump_hex.h"
#include "../includes/dump_tools.h"
#include <unistd.h>

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
