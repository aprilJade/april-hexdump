/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cntl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:42:24 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 22:26:55 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_CNTL_H
#define STR_CNTL_H

void ft_putstr(char *str);
int printError(char *file_path);
int ft_strncmp(char *s1, char *s2);
int ft_strlen(char *str);
void printFdError(char *file_path);

#endif
