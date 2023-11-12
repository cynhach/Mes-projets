#include <math.h>
#include <openssl/sha.h>

#include "generateData.h"
#include "winner.c"
#include "maths.h"
#include "rsa.h"
#include "key.h"
#include "signature.h"
#include "protected.h"
#include "listKey.h"
#include "listProtected.h"
#include "tree.h"

void testPremier() {
	unsigned long temps_initial;
	unsigned long temps_final;
	double temps_cpu;

	char* nom = "tempsPremier.txt";
	FILE* fichier = fopen(nom, "w");
	for(int p = 1; p < 900000000; p+=2) {
		temps_initial = clock();
		is_prime_naive(p);
		temps_final = clock();
		temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;
		fprintf(fichier, "%d %lf\n", p, temps_cpu);
	}
	fclose(fichier);
}

// Performances des deux methodes d'exponentiation modulaire
void testModPow() {
	unsigned long temps_initial_1;
	unsigned long temps_final_1;
	double temps_cpu_1;

	unsigned long temps_initial_2;
	unsigned long temps_final_2;
	double temps_cpu_2;
	
	long a = 2542521315020;
	long n = 3281365811;
	FILE* fichier = fopen("sortieTempsExpo.txt", "w");
	long m;
	for(m = 10; m <= 100000; m+= 1000) {
		temps_initial_1 = clock();
		modpow_naive(a,m,n);
		temps_final_1 = clock();
		temps_cpu_1 = ((double)(temps_final_1 - temps_initial_1)) / CLOCKS_PER_SEC;

		temps_initial_2 = clock();
		modpow(a,m,n);
		temps_final_2 = clock();
		temps_cpu_2 = ((double)(temps_final_2 - temps_initial_2)) / CLOCKS_PER_SEC;

		fprintf(fichier, "%ld %lf %lf\n", m ,temps_cpu_1, temps_cpu_2); 
	}	
	fclose(fichier);
}

void testMillerRabin() {
    long p,k;
    int nb_essais = 50;
    int echecs = 0;
    FILE* fichier = fopen("fiabiliteMillerRabin.txt","w");
    fprintf(fichier,"%20s %20s\n","p","erreur?");
    for (long i = 0; i <= nb_essais; i++) {
        p = rand_long(2,2147483647);
        k = rand_long(1,43);
        int pm = is_prime_miller(p,k);
        if (pm != is_prime_naive(p))  {
            fprintf(fichier,"%20ld %20s\n",p,"erreur");
            echecs++;
        } else {
            fprintf(fichier,"%20ld %20s\n",p,"pas d'erreur");
        }
    }
    fprintf(fichier,"La Probabilité d'erreur du test Miller-Rabin est de  ");
    fprintf(fichier,"%20f\n",((double)(echecs))/((double)(nb_essais)));
    fclose(fichier);
}

// Test du protocole RSA
void testProtocoleRSA() {
	// Generation de cle :
	long p = random_prime_number(3, 7, 5000);
	long q = random_prime_number(3, 7, 5000);
	while(p == q) {
		q = random_prime_number(3, 7, 5000);
	}
	printf("p = %ld\n", p);
    printf("q = %ld\n", q);
	long n, s, u;
	generate_key_values(p, q, &n, &s, &u);
	// Pour avoir des cles positives
	if(u < 0) {
		long t = (p-1)*(q-1);
		u = u + t;	// On aura toujours s*u mod t = 1 
	} 
	// Affichage des cles en hexadecimal
	printf("cle publique = (%lx, %lx) \n", s, n);
	printf("cle privee = (%lx, %lx) \n", u, n);

	// Chiffrement 
	char message[10] = "Hello";
	int len = strlen(message);
	long* crypted = encrypt(message, s, n);
	printf("Initial message : %s \n", message);
	printf("Encoded representation : \n");
	print_long_vector(crypted, len);

	// Dechiffrement 
	char* decoded = decrypt(crypted, len, u, n);
	printf("Decoded : %s\n", decoded);

	free(crypted);
	free(decoded);
}

void testKeys() {
	// Testing Init Keys
	Key* pKey = malloc(sizeof(Key));
	Key* sKey = malloc(sizeof(Key));
	init_pair_keys(pKey, sKey, 3, 7);
	printf("pKey : %lx, %lx \n", pKey->val, pKey->n);
	printf("sKey : %lx, %lx \n", sKey->val, sKey->n);
	
	// Testing Key Serialization 
	char* chaine = key_to_str(pKey);
	printf("key_to_str : %s \n", chaine);
	Key* k = str_to_key(chaine);
	printf("str_to_key : %lx, %lx \n", k->val, k->n);
	
	// Testing signature
	// Candidate keys :
	Key* pKeyC = malloc(sizeof(Key));
	Key* sKeyC = malloc(sizeof(Key));
	init_pair_keys(pKeyC, sKeyC, 3, 7);
	
	// Declaration
	char* mess = key_to_str(pKeyC);
	printf("%s vote pour %s\n", key_to_str(pKey), mess);
	Signature* s = sign(mess, sKey);
	printf("Signature : ");
	print_long_vector(s->content, s->size);
	chaine = signature_to_str(s);
	printf("signature_to_str : %s\n", chaine);
	s = str_to_signature(chaine);
	printf("str_to_signature : ");
	print_long_vector(s->content, s->size);
	
	// Testing protected :
	Protected* pr = init_protected(pKey, mess, s);
	
	// Verification :
	if(verify(pr)) {
		printf("Signature valide.\n");
	} else {
		printf("Signature non valide.\n");
	}
	
	chaine = protected_to_str(pr);
	printf("protected_to_str : %s\n", chaine);
	pr = str_to_protected(chaine);
	printf("str_to_protected : %s %s %s\n", key_to_str(pr->pKey), pr->mess, signature_to_str(pr->sign));
	
	free(mess);
	free(chaine);
	free(k);
	free(pKey);
	free(sKey);
	free(pKeyC);
	free(sKeyC);
	liberer_sign(s);
	liberer_protected(pr);
}

void testList() {
  	CellKey* keyList = read_public_keys("keys.txt");
  	print_list_keys(keyList);
  	delete_list_keys(keyList);
  	CellProtected* prList = read_protected("declarations.txt");
  	print_list_protected(prList);
  	delete_list_protected(prList);
  	
  	CellProtected* prList2 = read_protected("declarations.txt");

  	// Cleaning the list
  	supprimeFraude(&prList2);
  	print_list_protected(prList2);
  	delete_list_protected(prList2);
}

void testWinner() {
    CellKey* voters = read_public_keys("keys.txt");
	CellKey* candidates = read_public_keys("candidates.txt");
	CellProtected* declaration = read_protected("declarations.txt");
	Key* winner = compute_winner(declaration, candidates, voters, 20, 50);
    char* str = key_to_str(winner);
    printf("Le gagnant est : %s\n", str);

    free(str);
    delete_list_protected(declaration);
    delete_list_keys(voters);
    delete_list_keys(candidates);
}

void testSSL() {
	unsigned char* s = (unsigned char*)"Rosetta code";
	unsigned char* d = SHA256((const unsigned char*) s, strlen((const char*)s), 0);
	int i;
	for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
		printf("%02x", d[i]);
	putchar('\n');
}

void testComputeProofOfWork() {
	Block* b = (Block*) malloc(sizeof(Block));
    b->author = (Key*) malloc(sizeof(Key));
    init_key(b->author, 558, 133);
    b->votes = read_protected("declarations.txt");
    b->nonce = 0;
    b->hash = NULL;
    b->previous_hash = NULL;
    //char* strb = block_to_str(b);
    b->hash = (unsigned char *)strdup("hash");
    b->nonce = 550;
    free(b->hash);
    FILE* fichier = fopen("computeProof.txt", "w");
    for(int d = 1; d < 4.0; d++) {
    	clock_t begin = clock();
    	compute_proof_of_work(b, d);
   		clock_t end = clock();
    	fprintf(fichier, "%d %.3f\n", d, (double)(end-begin)/ CLOCKS_PER_SEC);
    }
    fclose(fichier);    
}

int main(void) {
	srand(time(NULL));
	
	//testPremier();
	//testModPow();
	//testMillerRabin();
	//testProtocoleRSA();
	//testKeys();
	//generate_random_data(20, 3);
	//testList();
	//testWinner();
	//testSSL();
	//testComputeProofOfWork();

	return 0;
}
