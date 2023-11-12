#include "rsa.h"

long extended_gcd(long s, long t, long* u, long* v) {
	if(t == 0) {
		*u = 1;
		*v = 0;
		return s;
	}
	long uPrim, vPrim;
	long gcd = extended_gcd(t, s%t, &uPrim, &vPrim);
	*u = vPrim;
	*v = uPrim-(s/t)*vPrim;
	return gcd;
}

void generate_key_values(long p, long q, long* n, long* s, long* u) {
	*n = p * q;
	int t = (p - 1) * (q - 1);
	long v;
	*s = rand_long(2, t);	// Genere s < t jusqu'à trouver PGCD(s,t) = 1 
	while(extended_gcd(*s, t, u, &v) != 1) {
		*s = rand_long(2, t);
	}
}

long* encrypt(char* chaine, long s, long n) {
	long* res = (long*) malloc(sizeof(long)*strlen(chaine));
	int i = 0;
	while(chaine[i] != '\0') {
		res[i] = modpow(chaine[i], s, n);
		i++;
	}
	return res;
}

char* decrypt(long* crypted, int size, long u, long n) {
	char* res = (char*) malloc(sizeof(char)*size+1);
	for(int i = 0; i < size; i++) {
		res[i] = (char)modpow(crypted[i], u, n);
	}
	res[size] = '\0';
	return res;
} 

void print_long_vector(long* result, int size) {
	printf("Vector : [");
	for(int i = 0; i < size; i++) {
		printf("%ld \t", result[i]);
	}
	printf("]\n");
}
