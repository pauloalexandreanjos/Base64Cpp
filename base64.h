#ifndef BYTE
#define BYTE unsigned char
#define PBYTE BYTE*
#endif
#include <cstring>
#include <cmath>

int getBaseValue(int pos);

const char base64mapping[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int base64Encode(PBYTE ,int, char* , int);

int base64Decode(char*, int, PBYTE, int);

int findChar(const char *, int, char);



