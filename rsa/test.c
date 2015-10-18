#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include "rsa.h"

void testhctoi();
void testitohc();
void testadd();
char* getrandhxstr(int len);
int random(int n);

void test()
{
	testhctoi();
	testitohc();
	testadd();
}

void testadd()
{
	char *l, *r;
	int i = 0, j = 0, k = 0;
	l = (char*)malloc(sizeof(char)*1024);
	r = (char*)malloc(sizeof(char)*1024);
	memset(l, 0, sizeof(char)*1024);
	memset(r, 0, sizeof(char)*1024);
	while(1){
		scanf("%s %s %d", l, r, &i);
		printf("l is %s, r is %s, base is %d\n", l, r, i);
		getchar();
		add(l, r, i);
	}
	
	/*
	while(i < 100){
		l = getrandhxstr(random(1024));
		printf("l's len is %d\n", strlen(l));
		r = getrandhxstr(random(1024));
		printf("r's len is %d\n", strlen(r));
		printf("l is %s, r is %s\n", l, r);
		if(strcmp(hcadd(l, r), add(l, r)) != 0)
		{
			printf("%s\n", "error");
		}
		
		i ++;
	}//*/
}
char* getrandhxstr(int len)
{
	char  num[17]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	char *l;
	int i = 0, offset = 0;
	if((l = (char*)malloc(sizeof(char)*(len+1))) == NULL) return NULL;

	memset(l, 0, sizeof(char)* (len+1));
	while(i < len){
		offset = random(17);
		*(l + i ) = num[offset];
		i ++;
	}
	return l;
}
int random(int n)
{
	srand((unsigned)(time(NULL)));
	return rand()%n;
}
void testhctoi()
{
	int i = 0;
	char c = '0', d = 'a', e = 'A';

	while(i < 10){
		if (i != ctoi(c))
		{
			printf("hctoi error %c\n", c);
		}
		i ++; c ++;
	}
	while(i < 16){
		if (i != ctoi(d))
		{
			printf("hctoi error %s\n", d);
		}
		if (i != ctoi(e))
		{
			printf("hctoi error %s\n", e);
		}
		i ++; d ++; e ++;
	}
	printf("testhctoi success\n");
}
void testitohc()
{
	int i = 0;
	char c[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	while(i < 16)
	{
		//printf("%c\n", itohc(i));
		if(c[i] != itoc(i, 16))
		{
			printf("itohc error %s\n", i);
		}
		i ++;
	}
	printf("testitohc success\n");
}