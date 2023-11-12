#ifndef BLOCK_H
#define BLOCK_H

#include "hash.h"

typedef struct block {
	Key* author;
	CellProtected* votes;
	unsigned char* hash;
	unsigned char* previous_hash;
	int nonce;
} Block;

Block* create_block(Key* author, CellProtected* votes, unsigned char* hash, unsigned char* previous_hash, int nonce);
void save_block(FILE* file, Block* b);
Block* read_block(char* file);
char* block_to_str(Block* block);
unsigned char* hash_function_block(const char* str);
void compute_proof_of_work(Block* B, int d);
int verify_block(Block* b, int d);
void delete_block(Block* b);

#endif
