#ifndef SIGNATURE_H
#define SIGNATURE_H

#include "key.h"

typedef struct _signature {
	long* content;
	int size;
} Signature;

Signature* init_signature(long* content, int size);
Signature* sign(char* mess, Key* sKey);
void liberer_sign(Signature* sign);
char* signature_to_str(Signature* sign);
Signature* str_to_signature(char* str);

#endif
