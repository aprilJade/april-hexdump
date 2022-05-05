/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:50:41 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 22:30:02 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../includes/dump_hex.h"
#include "../includes/str_cntl.h"

int	check_opt_c(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "-C") != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		option_flag;
	char	buf[16];

	if (argc > 0)
	{
		option_flag = check_opt_c(argc, argv);
		if ((!option_flag && argc == 1) || (option_flag && argc == 2))
			return (dump_hex_dynamic(option_flag));
		else
			return (dump_hex(argc, argv, option_flag, buf));
	}	
}
