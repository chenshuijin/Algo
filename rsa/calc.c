#include "calc.h"

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
 		else tmp = c2i(*(s+i));
 		tmp += c2i(*(result + i)) + c;
 		if(tmp > base - 1) {
 			c = tmp/base;
 			tmp -= base;
 		}
 		else c = 0;
 		*(result+i) = i2c(tmp, base);
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


