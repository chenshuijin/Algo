#include "tool.h"

unsigned char *bcd2hex(char *s) {
	int i = 0, tmp, l;
	unsigned char *r;

	l = strlen(s);
	if (l%2 != 0) {
		return NULL;
	}

	if ((r = allocinitmem(sizeof(char), 0, l/2 + 1)) == NULL) {
		return NULL;
	}
	i = 0;
	while(i < l/2) {
		printf("2i[%d],2i+1[%d]\n", *(s + 2*i)-48, *(s + 2*i + 1)-48);
		*(r+i)=((*(s + 2*i)-48)<<4)|(*(s + 2*i + 1) -48);
		printf("%d\n", *(r+i));
		i ++;
	}
	return r;
}

void* allocinitmem(unsigned int size, int value, unsigned int length) {
	void *ret;
	if((ret = (void*)malloc(size * length)) == NULL) return NULL;
	memset(ret, value, size * length);
	return ret;
}

void reverse(char *p) {
	int len = strlen(p), i = 0;
	char tmp;
	while(i < len/2)
	{
		tmp = *(p+i);
		*(p + i) = *(p + len - 1 - i);
		*(p + len - 1 - i) = tmp;
		i ++;
	}
}

int c2i(char c) {
	switch(c&0xf0){
		case 0x30:
			return c&0x0f;
		case 0x40:
		case 0x60:
		return (c&0x0f) + 9;
		default:
			return c;
	}
}

char i2c(int i, int base) {
	if (i >= 0 && i < base)
	{
		if(i <= 9)
			return (char)(i | 0xf0 & 0x3f);
		else
			return (char)((i-9) | 0xf0 & 0x4f);
	}
	else return (char)i;
}

void trimstart(char *s, char c) {
	int i = 0, l = 0, j = 0;
	l = strlen(s);
	while(i < l - 1){
		if(*(s+i) != c) break;
		i ++;
	}
	if (i <= 0)
	{
		return;
	}
	memset(s, 0, sizeof(char)*i);
	while(j < l - i)
	{
		*(s + j) = *(s + i + j);
		*(s + i + j) = 0;
		j++;
	}
	memset(s+l-i, 0, sizeof(char)*i);
}

void print(char *p) {
	printf("%s\n", p);
}

