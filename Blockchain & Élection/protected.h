#ifndef PROTECTED_H
#define PROTECTED_H

#include "signature.h"

typedef struct _protected {
	Key* pKey;
	char* mess;
	Signature* sign;
} Protected;

Protected* init_protected(Key* pKey, char* mess, Signature* sign);
int verify(Protected* pr);
char* protected_to_str(Protected* pr);
Protected* str_to_protected(char* mess);
void liberer_protected(Protected* pr);

#endif
