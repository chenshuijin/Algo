#include<stdio.h>

#include "sort.h"


void test_divid_cmbine_sort();

void printArray(int *a, int len);

typedef void (*CALLBACK)(void *p);



void call(CALLBACK pCallBack, char *p);

void Bfuc(char * p);
void Afuc(char * p);
void mycallback(void *pfuc(int), int n);
