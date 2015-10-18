#include <stdio.h>
#include "rsa.h"

void reverse(char *p);
void print(char *p);
void trimstart(char *s, char c);
int ctoi(char c);
char itoc(int i, int base);
void* allocinitmem(unsigned int size, int value, unsigned int length);

char* add(char *l, char *r, int base)
{
	int lenl = 0, lens = 0, len = 0, i = 0, c = 0, tmp = 0;
	char *result, *s;
	trimstart(l, '0'); trimstart(r, '0');
	lenl = strlen(l); lens = strlen(l);
	len = lenl > lens ? lenl + 2 : lens + 2;
	printf("l is %s, r is %s, base is %d\n", l, r, base);
	if((result = (char*)allocinitmem(sizeof(char), 0, len)) == NULL)
	{
		printf("%s\n", "malloc list error.");
		return NULL;
	}
	reverse(l);reverse(r);
	if (lenl > lens) {
		strcpy(result, l);
		s = r;
	}
	else {
		strcpy(result, r);
		s = l;
		lens = lenl;
	}
 	i = 0, c = 0;
 	while(1){
 		if(i >= lens){
 			if(c <= 0) break;
 		}
 		else tmp = ctoi(*(s+i));
 		tmp += ctoi(*(result + i)) + c;
 		if(tmp > base - 1) {
 			c = tmp/base;
 			tmp -= base;
 		}
 		else c = 0;
 		*(result+i) = itoc(tmp, base);
 		i ++; tmp = 0;
 	}
	reverse(l);reverse(r);reverse(result);

#ifdef DEBUG
 	printf("%s + %s = %s\n", l, r, result);
#endif
	return result;
}

char* minus(char *l, char *r, int base)
{
	return "";
}

void* allocinitmem(unsigned int size, int value, unsigned int length)
{
	void *ret;
	if((ret = (void*)malloc(size * length)) == NULL) return NULL;
	memset(ret, value, size * length);
	return ret;
}

void reverse(char *p)
{
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

int ctoi(char c)
{
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

char itoc(int i, int base)
{
	if (i >= 0 && i < base)
	{
		if(i <= 9)
			return (i | 0xf0 & 0x3f);
		else
			return ((i-9) | 0xf0 & 0x4f);
	}
	else return i;
}

void trimstart(char *s, char c)
{
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

void print(char *p)
{
	printf("%s\n", p);
}


