#include "main.h"
void loadUtildll();
int main(int argc, char const *argv[])
{
	char buf[1024];
	int a, b, res;
	char *mystr = "calculating...\n";
	char *emsg = "error in adding\n";

	a = 5; b = 10;
	printf("%s\n", mystr);
	//Hello();
    //IncCounter();
	//a = GetMod(1, 2);
	printf("%s\n", mystr);
	printf("%d\n", a);
	test();
	//loadUtildll();
	//getchar();
	return 0;
}
void loadUtildll()
{
	HINSTANCE	hdll;
	hdll = LoadLibrary("util.dll");
	lIntAdd = (lpIntAdd)GetProcAddress(hdll, "GetMod");
	printf("%d\n", lIntAdd(2,3));
	printf("%s\n", "yes");
	lHello = (lpVoid)GetProcAddress(hdll, "Hello");
	lHello();
	FreeLibrary(hdll);
}