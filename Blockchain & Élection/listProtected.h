#ifndef LISTPROTECTED_H
#define LISTPROTECTED_H

#include "protected.h"

typedef struct cellProtected {
	Protected* data;
	struct cellProtected* next;
} CellProtected;

CellProtected* create_cell_protected(Protected* pr);
CellProtected* inserer_en_tete_protected(CellProtected** LCP, Protected* pr);
CellProtected* read_protected(char* file);
void print_list_protected(CellProtected* LCP);
void delete_cell_protected(CellProtected* cp);
void delete_list_protected(CellProtected* LCP);
void supprimeFraude(CellProtected **LCP);
CellProtected* fusion_list_protected(CellProtected* votes1, CellProtected* votes2);

#endif
