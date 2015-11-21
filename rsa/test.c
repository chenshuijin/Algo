#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>
#include "test.h"

void testhctoi();
void testitohc();
void testadd();
char* getrandhxstr(int len);
int random(int n);
void testTlv();

void test()
{
	//testhctoi();
	//testitohc();
	//testadd();
	testTlv();
}
void testTlv(){
	unsigned char *s = "30818902818100C7C805725BEF2BF41D15F37BD09B5FFF67632593362154D2AE8BCA7A398928BAB91861D77A56A263823D72AFB6F59327AFEDD11F8B79F7E782CE8E920790AFDB6E1D2B7E214763AC4BE1638E239F762344761B60586C3A85A3FB6AAF11D84903D71202DF393B22E2CCB276584EF6AC214309CD4DFD7EA602902E57D1023A7C410203010001";
	unsigned char *r;
	TLV *tlv;
	s="3082025D02010002818100C7C805725BEF2BF41D15F37BD09B5FFF67632593362154D2AE8BCA7A398928BAB91861D77A56A263823D72AFB6F59327AFEDD11F8B79F7E782CE8E920790AFDB6E1D2B7E214763AC4BE1638E239F762344761B60586C3A85A3FB6AAF11D84903D71202DF393B22E2CCB276584EF6AC214309CD4DFD7EA602902E57D1023A7C4102030100010281810082C997873E585D55FA949C49BA4F7D911E85F1DB65DC7C4350B1836470B6324BCB5102FCA5C2819CD36E96DE21D0B2FD90570848B66EAAB48D15DC900D13D38B928A8F10D0F71795B1AA52B35EA19B1A9146056BFB68908529629008C526B863D643220AB073FEAEE001B2D6DB986944A3EB1C2D832EBDB4B84AB5E00444B481024100F4C62AC200A69F2A71877B8775CF37FE69BAE7ED9D63E0F43267031AFAFB1EB73B616EA964BB8CF5C38BEDC53BDF0A744A05DB159DAD5413696C845E5402CAAD024100D0F19AF1E054884916D4A743A0C0935339E908AA86F993943FA6ADAE37847106C7D9AD303AF1C58C3CF062B7BE76A45193F6883EF72886908DB94ADD05295E65024025A3EBA355B249BB9F25B46B4A448959C82C83C9D8702981A3D68F75B0AEB934781F2D8343084C4EE6B937E122A9D3D3BA2658606494E8DEEB5152B1A6BD9F2902402B91050EC408BC360935A3FEBCE90A8F02F72D20696E66B035A96A73760DFE873C6A8DEB0D8F55F28CCE4EB7235697A28EE88BB61D50ECE5FD37127E0D5277E50241009F59B4AC287BBC881B5338CE559199B406DC1A1E5DB63B61798A067A60B05F66DA71B74D32DE9185A8AD6763FCAF9EA407A29431F0031ECB958D82861E38F51180000000000000";
	printf("[%s]\n", s);
	//r = bcd2hex(s);
	//printf("exchange[%s]\n", r);
	tlv = Parse(s);
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
		if (i != c2i(c))
		{
			printf("hctoi error %c\n", c);
		}
		i ++; c ++;
	}
	while(i < 16){
		if (i != c2i(d))
		{
			printf("hctoi error %s\n", d);
		}
		if (i != c2i(e))
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
		if(c[i] != i2c(i, 16))
		{
			printf("itohc error %s\n", i);
		}
		i ++;
	}
	printf("testitohc success\n");
}