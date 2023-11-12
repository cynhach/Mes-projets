#ifndef KEY_H
#define KEY_H

#include "rsa.h"

typedef struct _key {
	long val;
	long n;
} Key;

Key* create_key();
void init_key(Key* key, long val, long n);
void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size);
char* key_to_str(Key* key);
Key* str_to_key(char* str);

#endif
