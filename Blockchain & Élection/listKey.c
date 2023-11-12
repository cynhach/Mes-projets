#include "listKey.h"

CellKey* create_cell_key(Key* key){
	CellKey* cell = (CellKey*) malloc(sizeof(CellKey));
	if(cell == NULL) {
		fprintf(stderr, "%s; %s; l.%d: CellKey Allocation Error\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
	}
	cell->data = key;
	cell->next = NULL;
	return cell;
}

void inserer_en_tete_key(CellKey** list, Key* key) {
	CellKey* cell = create_cell_key(key);
	cell->next = *list;
	*list = cell;
}

CellKey* read_public_keys(char* file) {
	FILE* fichier = fopen(file, "r");
	if(fichier == NULL) {
		fprintf(stderr, "%s; %s; l.%d: Can't open the file: %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, file);
    	exit(EXIT_FAILURE);
	}
	char pKey[256];
	char buffer[256];
	CellKey* list = NULL;		
	while (fgets(buffer, 256, fichier) != NULL) {
    	if(sscanf(buffer, "%s", pKey) != 1) {
    		fprintf(stderr, "%s; %s; l.%d: Invalid Key Format\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
      		exit(EXIT_FAILURE);
    	}
    	inserer_en_tete_key(&list, str_to_key(pKey));
    } 
    fclose(fichier); 
    return list;
}

void print_list_keys(CellKey* LCK) {
	char* key;
	while(LCK != NULL) {
		key = key_to_str(LCK->data);
        printf("%s\n", key);
        free(key);
        LCK = LCK->next;
    }
}

void delete_cell_key(CellKey* CK) {
	free(CK->data);
	free(CK);
}

void delete_list_keys(CellKey* LCK) {
	CellKey *tmp;
    while(LCK){
        tmp = LCK->next;
        delete_cell_key(LCK);
        LCK = tmp;
    }
}

