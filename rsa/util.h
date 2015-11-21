#ifndef __windows_h__
    typedef unsigned long DWORD;
    #define STDCALL _stdcall
#endif

//void STDCALL IncCounter();
//void STDCALL DecCounter();
int  STDCALL GetMod(int a, int b);
void STDCALL Hello();

typedef int (STDCALL *lpIntAdd) (int, int);
typedef void (STDCALL *lpVoid) ();
typedef	char *(STDCALL *lpChar) (char *l, char *r);
lpVoid lHello;
lpIntAdd lIntAdd;
lpChar lAdd;
