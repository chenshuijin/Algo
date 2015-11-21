#include<stdio.h>
#include<string.h>
#include<math.h>

#ifndef __windows_h__
    typedef unsigned long DWORD;
    #define STDCALL _stdcall
#endif

#ifndef DDD
#define  DDD 1
#endif

typedef struct TLV{
	unsigned char *Tag;
	unsigned char *Length;
	unsigned char *Contents;
	struct TLV *Prix;
	struct TLV *Next;
	struct TLV *Childs;
} TLV;

TLV   *Parse(unsigned char *input);
void PrintTlv(TLV *tlv);