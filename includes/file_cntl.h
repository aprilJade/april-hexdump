#ifndef FILE_CNTL_H
# define FILE_CNTL_H

int		file_open(char *file_path);
int		get_file_size(char *file_path);
int		dup_file(char *file_path, int size, char **data);
int		check_file(char *file, int *i);

#endif
