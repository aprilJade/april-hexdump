#ifndef HEX_DUMP_TOOLS_H
#define HEX_DUMP_TOOLS_H
#define BUFFER_SIZE 16

void printLine(char *data, int total_size, int size, int flag);
void PrintIndexInHex(int size, int flag, int last);
void PrintDataInHex(unsigned char *data, int size, int flag);
void PrintDataInAscii(unsigned char *data, int size);
void PrintRemainData(char *data, int size, int flag);
void charcat(char *dest, char c);
void PrintSpaces(int len, int flag);
void PrintIntinHex(int number, const char *hex);

#endif
