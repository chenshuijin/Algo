#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse(char *p);
void print(char *p);
void trimstart(char *s, char c);
int c2i(char c);
char i2c(int i, int base);
void* allocinitmem(unsigned int size, int value, unsigned int length);
char *bcd2hex(char *s);