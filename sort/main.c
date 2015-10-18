#include"main.h"

int main(int argc, char **argv)
{
	printf("yes\n");
	char *p = "sdfasdf";
	char *t = "a";
	test_divid_cmbine_sort();
	getchar();
}

/*
test the divide combine sort
*/
void test_divid_cmbine_sort()
{
	int a[] = { 1, 3, 9, 100, 4, 32, 232, 54, 1, 43, 54, 145, 234, 987, 456, 43, 67, 43, 56, 32 };
	int *b = a;
	printf("%d %d\n", sizeof(a), sizeof(b));
	printf("before sort:");
	printArray(a, 19);
	divid_cmbine_sort(a, 0, 19);
	printf("after sort:");
	printArray(a, 19);
}

/*
print the array to the console
*/
void printArray(int *a, int len)
{
	int i = 0;

	while (i <= len)
	{
		printf("%d ", a[i]);
		i = i + 1;
	}
	printf("\n");
}

void call(CALLBACK pCallBack, char *p)
{
	printf("call\n");
	pCallBack((void *)p);
}

void Afuc(char * p)
{
	int i = 0;
	while (i < 100)
	{
		printf("Afuc %d ", p);
		p++;
		i++;
		//_sleep(50);
	}
	printf("\nend print\n");
}
void Bfuc(char * p)
{
	int i = 0;
	while (i < 100)
	{
		printf("Bfuc %d ", p);
		p++;
		i++;
		//_sleep(50);
	}
	printf("\nend print\n");
}