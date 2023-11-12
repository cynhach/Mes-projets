#include "key.h"

Key* create_key() {
  	Key *key = (Key *) malloc(sizeof(Key));
	if (key == NULL) {
    	fprintf(stderr, "%s; %s; l.%d: Key Allocation Error\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
  	}
	return key;
}

void init_key(Key* key, long val, long n) {
	key->val = val;
	key->n = n;
}

void init_pair_keys(Key* pKey, Key* sKey, long low_size, long up_size) {
	int k = rand()%10000;
	long p = random_prime_number(low_size, up_size, k);
	long q = random_prime_number(low_size, up_size, k);
	long n, s, u;
	generate_key_values(p, q, &n, &s, &u);
	if(u < 0) {
        long t = (p-1)*(q-1);
        u = u + t;
    }
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

char* key_to_str(Key* key) {
	char buffer[256];
	sprintf(buffer, "(%lx,%lx)", key->val, key->n);
	return strdup(buffer);
}

Key* str_to_key(char* str) {
	Key* key = (Key*) malloc(sizeof(Key));
	long val;
	long n;
	sscanf(str, "(%lx,%lx)", &val, &n);
	init_key(key, val, n);
	return key;
}




