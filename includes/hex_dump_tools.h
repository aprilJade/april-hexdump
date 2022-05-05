#ifndef HEX_DUMP_TOOLS_H
#define HEX_DUMP_TOOLS_H
#define BUFFER_SIZE 16

void PrintIntinHex(int number, char *hex);
void PrintIndexInHex(int size, int flag, int last);
void PrintDataInHex(unsigned char *data, int size, int flag);
void PrintDataInAscii(unsigned char *data, int size);
void printLine(char *data, int total_size, int size, int flag);
void PrintSpaces(int len);
void read_error(int fd, char *file_path);
void PrintRemainData(char *data, int size, int flag);
void init_buffer(char *buffer);
void charcat(char *dest, char c);
int check_read_error(char buf[16], char *file, int size, int fd);
int check_size_limit(int fd, int size);
int memory_compare(char s1[BUFFER_SIZE], char s2[BUFFER_SIZE]);
void memory_copy(char dest[BUFFER_SIZE], char src[BUFFER_SIZE]);
int check_overlap(char buf[16], char tmp[16], int *size, int *is_overlap);

#endif
