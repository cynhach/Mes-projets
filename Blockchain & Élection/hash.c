#include "hash.h"

HashCell* create_hashcell(Key* key) {
    HashCell* hc = (HashCell*) malloc(sizeof(HashCell)); 
    if (hc == NULL) {
    	fprintf(stderr, "%s; %s; l.%d: HashCell Allocation Error\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
  	}
    hc->key = key;
    hc->val = 0; 
    return hc; 
}

int hash_function(Key* key, int size) {
    double A = (sqrt(5.) - 1)/2 ;	// Nombre d’or auquel on soustrait 1
    long k = key->val; 
    int h = (int)(floor(size*(k*A-floor(k*A)))); 
    return h;
}

int find_position(HashTable* t, Key* key) {
	int n = t->size;
	int h = hash_function(key, n);
	int i = 0;
	int indice = (h+i)%n;
	//Probing lineaire
	while((t->tab)[indice] != NULL) {
		if(((((t->tab)[indice])->key)->val == key->val) && ((((t->tab)[indice])->key)->n == key->n)) {
			return indice;
		}
		i += 1;
		indice = (h+i)%n;
	}
    return indice;
}

HashTable* create_hashtable(CellKey* keys, int size) {
    int pos;
    HashTable *ht = (HashTable*) malloc(sizeof(HashTable)) ; 
    if(ht == NULL) {
        fprintf(stderr, "%s; %s; l.%d: HashTable Allocation Error\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
    }
    ht->size = size ; 
    ht->tab = (HashCell**) malloc(sizeof(HashCell)*size);
    if((ht->tab) == NULL) {
    	free(ht);
    	fprintf(stderr, "%s; %s; l.%d: HashTable->Tab Allocation Error\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
    } 
    for(int i = 0; i < size; i++) {
    	(ht->tab)[i] = NULL;
    }
    while(keys != NULL) {
    	pos = find_position(ht, keys->data);
        (ht->tab)[pos] = create_hashcell(keys->data);
        keys = keys->next;
    }
    return ht; 
}

void delete_hashcell(HashCell* hc) {
    free(hc->key);
    free(hc); 
}

void delete_hashtable(HashTable* t) {
    for (int i = 0; i < t->size; i++) {
    	if ((t->tab)[i] != NULL) {
      		free((t->tab)[i]);
    	}
  	}
  // Free the memory used by the array
  free(t->tab);
  free(t);
}
