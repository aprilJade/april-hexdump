/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_cntl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggyk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:29:05 by seonggyk          #+#    #+#             */
/*   Updated: 2022/04/30 22:45:38 by seonggyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_CNTL_H
# define FILE_CNTL_H

int		file_open(char *file_path);
int		get_file_size(char *file_path);
int		dup_file(char *file_path, int size, char **data);
int		check_file(char *file, int *i);

#endif
