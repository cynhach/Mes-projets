#include "block.h"

Block* create_block(Key* author, CellProtected* votes, unsigned char* hash, unsigned char* previous_hash, int nonce) {
	Block* block = (Block*) malloc(sizeof(Block));
	if(!block) {
		printf("Erreur d'allocation mémoire dans ecrireBlock.\n");
		return NULL;
	}
	block->author = author;
	block->votes = votes;
	block->hash = hash;
	block->previous_hash = previous_hash;
	block->nonce = nonce;
	return block;
}

void save_block(FILE* file, Block* b) {
	FILE* fichier = fopen(file, "w");
	CellProtected* tmp = b->votes;
	char* key = key_to_str(b->author);
	char* pr = NULL;

	fprintf(fichier, "%s %s %s %d\n", key, b->hash, b->previous_hash, b->nonce);
	free(key);
	while(tmp) {
		pr = protected_to_str(tmp->data);
		fprintf(fichier, "%s\n", pr);
		free(pr);
		tmp = tmp->next;
	}
	fclose(fichier);
}

Block* read_block(char* file) {
	FILE* fichier = fopen(file, "r");
	Block* b = (Block*) malloc(sizeof(Block));
	if(!file || !b) {
		printf("Erreur dans lireBlock.\n");
		return NULL;
	}
	char key[256];
	char pr[512];
	b->votes = NULL;
	char ligne[512];
	fgets(ligne, 512, fichier);
	sscanf(ligne, "%s %s %s %d", key, b->hash, b->previous_hash, &(b->nonce));
	b->author = str_to_key(key);
	while(fgets(ligne, 512, fichier)) {
		sscanf(ligne, "%s", pr);
		inserer_en_tete_protected(b->votes, str_to_protected(pr));
	}
	fclose(fichier);
	return b;
}

char* block_to_str(Block* block) {
	char* b = (char*) malloc(sizeof(char)*256);
    char* pr;
    int taille = 256;
    CellProtected* tmp = block->votes;
    sprintf(b,"%s %s %s %d\n", key_to_str(block->author), block->previous_hash, block->hash, block->nonce);
    while (tmp){
        pr = protected_to_str(tmp->data);
        taille += strlen(pr)+1;
        b = (char*) realloc(b, taille);
        strcat(b, pr);
        free(pr);
        tmp = tmp->next;
    }
    return b;
}

unsigned char* hash_function_block(const char* str) {
	return SHA256((const unsigned char*)str, strlen(str), 0);
}

int count(unsigned char* str) {
	int nb = 0;
	int taille = strlen((const char*)str);
	while((nb < taille) && (str[nb] == '0')) {
		nb++;
	}
	return nb;
}

void compute_proof_of_work(Block* B, int d) {
	B->nonce = 0;
	char* str = block_to_str(B);
	unsigned char* hash = hash_function_block((const char*) str);
	while(count(hash) < d) {
		free(str);
		B->nonce++;
		str = block_to_str(B);
		hash = hash_function_block((const char*) str);
	}
	B->hash = hash;
}

int verify_block(Block* b, int d) {
	char* str = block_to_str(b);
	unsigned char* hash = hash_function_block(str);
	return (count(hash) == d);
}

void delete_block(Block* b) {
	free(b->hash);
	free(b->previous_hash);
	CellProtected* tmp;
	while(b->votes) {
		tmp = b->votes->next;
		free(b->votes);
		b->votes = tmp;
	}
	free(b);
}