/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_hex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 10:57:43 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 10:58:48 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUMP_HEX_H
# define DUMP_HEX_H
# define BUFFER_SIZE 16

int	dump_hex_dynamic(int flag);
int	dump_hex(int argc, char **argv, int flag, char buf[BUFFER_SIZE]);

#endif
