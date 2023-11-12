#include <math.h>
#include "maths.h"

int is_prime_naive(long p) {
	if(p < 2)
		return 0;

	for(int i = 2; i < p; i++) {
		if(p%i == 0)
			return 0;
	}
	return 1;
}

long modpow_naive(long a, long m, long n) {
	long res = 1;
	for(int i = 0; i < m; i++) {
		res = (res*a)%n;
	}
	return res;
}

int modpow(long a, long m, long n){
	// Les cas de base
	if (a == 0)
		return 0;
	if (m == 0)
		return 1;

	// Si m est paire
	long b;
	if (m%2 == 0) {
		b = modpow(a, m/2, n);
		b = (b*b)%n;
	}

	// Si m est impaire
	else {
		b = a%n;
		b = (b*modpow(a, m-1, n)%n)%n;
	}
	return (b+n)%n;
}

//  Teste si a est un temoin de Miller pour p, pour un entier a donne 
int witness(long a, long b, long d, long p) {
	long x = modpow(a, d, p);
	if(x == 1) {
		return 0;
	}
	for(long i = 0; i < b; i++) {
		if(x == p-1) {
			return 0;
		}
		x = modpow(x, 2, p);
	}
	return 1;
}

// Retourne un entier long genere aleatoirement entre low et up inclus 
long rand_long(long low, long up) {
	return rand() % (up - low + 1) + low;
}

// Realise le test de Miller-Rabin en generant k valeurs de a au hasard 
int is_prime_miller(long p, int k) {
	if(p == 2) {
		return 1;
	}
	if(!(p & 1) || p <= 1) {	// On verifie que p est impair et different de 1 
		return 0;
	}
	// On determine b et d 
	long b = 0;
	long d = p - 1;
	while(!(d & 1)) {	// Tant que d n'est pas impair 
		d = d / 2;
		b = b + 1;
	}
	// On genere k valeurs pour a et on teste si c'est un temoin 
	long a;
	int i;
	for(i = 0; i < k; i++) {
		a = rand_long(2, p-1);
		if(witness(a,b,d,p)) {
			return 0;
			
		}
	}
	return 1;
}

long random_prime_number(int low_size, int up_size, int k) {
	long min = pow(2, low_size-1);
	long max = pow(2, up_size)-1;
	long number = rand_long(min,max);
	int prime = is_prime_miller(number,k);
	while(!prime){
		number = rand_long(min,max);
		prime = is_prime_miller(number,k);
		//printf("%ld, %d \n",number,is_prime_miller(number,k));
	}
	printf("%ld, %d \n",number,is_prime_miller(number,k));
	return number;
}