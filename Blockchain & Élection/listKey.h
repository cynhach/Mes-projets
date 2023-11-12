#ifndef LISTKEY_H
#define LISTKEY_H

#include "key.h"

typedef struct cellKey {
	Key* data;
	struct cellKey* next;
} CellKey;

CellKey* create_cell_key(Key* key);
void inserer_en_tete_key(CellKey** ck, Key* key);
CellKey* read_public_keys(char* file);
void print_list_keys(CellKey* LCK);
void delete_cell_key(CellKey* c);
void delete_list_keys(CellKey* c);

#endif
