/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cntl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:41:54 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 21:31:05 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include "../includes/str_cntl.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_path_error(char *file_path)
{
	ft_putstr("ft_hexdump: ");
	ft_putstr(basename(file_path));
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	ft_putstr("\n");
	return (8);
}

void	ft_print_fd_error(char *file_path)
{
	ft_putstr("ft_hexdump: ");
	ft_putstr(file_path);
	ft_putstr(": Bad file descriptor\n");
}

int	ft_strncmp(char *s1, char *s2)
{
	int	ret;

	ret = 0;
	while (ret == 0)
	{
		ret = *s1 - *s2;
		if (*s1 == 0 || *s2 == 0)
			return (ret);
		s1++;
		s2++;
	}
	return (ret);
}
