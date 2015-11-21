#include "asnber.h"

#ifndef DDD
typedef struct TLV{
	unsigned char *Tag;
	unsigned char *Length;
	unsigned char *Contents;
	struct TLV *Prix;
	struct TLV *Next;
	struct TLV *Childs;
} TLV;
#endif

enum LenForm
{
	ShortForm,
	LongForm,
	IndefLen
};
enum CntnType {
	primitive,
	constructed
};
enum TClass{
	universal,//bit8-bit7  0 0
	application,//bit8-bit7  0 1
	context_specific,//bit8-bit7  1 0
	private//bit8-bit7  1 1
};
typedef struct List
{
	void *curt;
	void *Next;
	void *Prix;
};

typedef struct Tag
{
	enum TClass Ttype;
	enum CntnType Ctype;
	unsigned char *Contents;
} Tag;
typedef struct TLen
{
	enum LenForm LForm;
	//the size of length octets
	unsigned char CSize;
	//the contents of length octets
	unsigned char *Contents;
} TLen;

unsigned char *CntsParse(unsigned char *input, TLen tlen);
TLen LenParse(unsigned char *input);
Tag TagParse(unsigned char *input);

TLV *Parse(unsigned char *input)
{
	int i = 0, indx = 0, taglen = 0, len=0, lenlen = 0, cntslen = 0;
	unsigned char curntc;
	TLV header, *tlv, curntTlv, tmpnode;
	Tag tmpTag; TLen tmpLen;
	//printf("===================================================\n");
	//printf("parse input[%s]\n", input);
	len = strlen(input);
	
	if((tlv = (TLV*)malloc(sizeof(TLV))) == NULL) return NULL;
	if(memset(tlv, 0, sizeof(TLV)) == NULL) return NULL;

	tmpTag = TagParse(input);
	tlv->Tag = tmpTag.Contents;
	indx += strlen(tlv->Tag);
	tmpLen = LenParse(input+indx);
	tlv->Length = tmpLen.Contents;
	indx += strlen(tlv->Length);
	tlv->Contents = CntsParse(input + indx, tmpLen);
	indx += strlen(tlv->Contents);

	//PrintTlv(tlv);
	//printf("parse indx[%d]\n", indx);
	switch (tmpTag.Ctype) {
		case primitive:
			tlv->Childs = NULL;
			tlv->Prix = NULL;
			if (indx < len)
				tlv->Next = Parse(input + indx);
			//printf("parse primitive[%x]\n", indx);
			break;
		case constructed:
			tlv->Childs = Parse(tlv->Contents);
			tlv->Prix = NULL;
			if (indx < len)
				tlv->Next = Parse(input + indx);
			//printf("parse constructed[%x]\n", indx);
			break;
		default:
			tlv->Childs = NULL;
			tlv->Next = NULL;
			tlv->Prix = NULL;
			//printf("parse default[%x]\n", indx);
			break;
	}
	//PrintTlv(tlv);
	return tlv;
}

Tag TagParse(unsigned char *input) {
	int indx = 0, taglen = 0, len; 
	unsigned char curtc, *tmpc, *tstr;
	Tag tag;

	len = strlen(input);
	curtc = (*input-48)<<4|(*(input+1)-48);
	indx += 2;
	tag.Ttype = curtc & 0xc0;
	tag.Ctype = (curtc&0x20)>>5;
	//printf("TagParse Ttype %d\n", tag.Ttype);
	//printf("TagParse Ctype %d\n", tag.Ctype);
	//primitive, definite-length method
	//constructed, definite-length method
	//if (curtc&0x20 != 0x20) {
	//low-tag-number form , default
	//high-tag-number form
	if (curtc&0x1f == 0x1f) {
		//high-tag-number form
		while((curtc = ((*(input+indx)-48)<<4|(*(input+indx+1))-48))&0x80==0x80 && indx < len)
			indx += 2;
	}
	taglen = indx;
	if((tstr = (unsigned char*)malloc(sizeof(unsigned char)*(taglen+1))) == NULL)
		return tag;
	memset(tstr, 0, sizeof(char)*(taglen+1));
	if(strncpy(tstr, input, taglen) == NULL)
		return tag;
	tag.Contents = tstr;
	return tag;
}

TLen LenParse(unsigned char *input) {
	int indx = 0;
	unsigned char curtc, *tmpContents;
	TLen tlen;

	curtc = (*input-48)<<4|(*(input+1)-48);
	//printf("-----------------------------------------\n");
	//printf("LenParse input[%s]\n", input);
	//printf("LenParse curtc&0x80[%x]\n", curtc&0x80);
	indx += 2;
	//if((tlen = (TLen)malloc(sizeof(TLen))) == NULL) return NULL;

	if (curtc == 0x80) {
		//indefinite-length
		tlen.LForm = 2;
		tlen.CSize = 0x01;
		//printf("LenParse indefinite[%x]\n", tlen.LForm);
	} else {
		//definite-length
		if ((curtc&0x80) != 0x80)
		{
			//short form
			tlen.LForm = 0;
			tlen.CSize = 0x01;
			//printf("LenParse short form[%x]\n", tlen.LForm);
		} else {
			//long form
			tlen.LForm = 1;
			tlen.CSize = (curtc & 0x7f) + 1;
			//printf("LenParse long form[%x]\n", tlen.LForm);
		}
	}
	if((tmpContents = (unsigned char*)malloc(sizeof(unsigned char) * (tlen.CSize*2+1))) == NULL) return tlen;
	if(memset(tmpContents, 0, tlen.CSize*2+1) == NULL) return tlen;
	if(strncpy(tmpContents, input, tlen.CSize*2) == NULL) return tlen;
	tlen.Contents = tmpContents;
	return tlen;
}

unsigned char *CntsParse(unsigned char *input, TLen tlen) {
	int i = 0, indx = 0, len, lenlen;
	unsigned char curtc, *ctsTmp, left, right;

	len = strlen(input);

	switch (tlen.LForm) {
		case ShortForm:
			indx = ((*tlen.Contents-48)<<4|(*(tlen.Contents+1)-48))&0x7f;
			//printf("CntsParse ShortForm indx[%x]\n", indx);
			break;
		case LongForm:
		//now, has bug
			i = 0;
			left = *(tlen.Contents)-48;
			right = *(tlen.Contents + 1)-48;
			curtc = (left<<4|right)&0x7f;
			//printf("CntsParse LongForm tlen.Contents[%s]\n", tlen.Contents);
			//printf("CntsParse LongForm left[%x]\n", left);
			//printf("CntsParse LongForm right[%x]\n", right);
			indx = 0;
			//printf("CntsParse LongForm curtc[%x]\n", curtc);
			while(i < curtc*2) {
				//printf("CntsParse LongForm tt[%d] left[%d]\n", (curtc+1)*2-i,*(tlen.Contents + (curtc+1)*2-i-1));
				left = *(tlen.Contents + (curtc+1)*2-i-1)-48;
				indx += (left)*pow(0x10, i);
				i += 1;
			}
			
			//printf("CntsParse LongForm indx[%x]\n", indx);
			break;
		case IndefLen:
		default:
			while(indx < len) {
				left = *(input + indx) - 48;
				right = *(input + indx + 1) - 48;
				curtc = left<<4|right;
				left = *(input + indx + 2) - 48;
				right = *(input + indx + 3) - 48;
				if (curtc == 0x00 && (left<<4|right == 0x00)) {
					break;
				}
				indx += 4;
			}
			indx /= 2;
			//printf("CntsParse IndefLen indx[%x]\n", indx);
	}
	if((ctsTmp = (unsigned char*)malloc(sizeof(unsigned char)*(indx*2 + 1))) == NULL) return ctsTmp;
	if(memset(ctsTmp, 0, indx*2 + 1) == NULL) return ctsTmp;
	if(strncpy(ctsTmp, input, indx*2) == NULL) return ctsTmp;
	return ctsTmp;
}

void PrintTlv(TLV *tlv)
{
	printf("tag[%s], length[%s], value[%s]\n", tlv->Tag, tlv->Length, tlv->Contents);
	if (tlv->Next != NULL){
		PrintTlv(tlv->Next);
	}
	if (tlv->Childs != NULL){
		PrintTlv(tlv->Childs);
	}
}