#include "listProtected.h"

CellProtected* create_cell_protected(Protected* pr) {
	CellProtected* cp = (CellProtected*) malloc(sizeof(CellProtected));
	if(cp == NULL) {
		fprintf(stderr, "%s; %s; l.%d: CellProtected Allocation Error\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
	}
	cp->data = pr;
	cp->next = NULL;
	return cp;
}

CellProtected* inserer_en_tete_protected(CellProtected** LCP, Protected* pr) {
	CellProtected* new = create_cell_protected(pr);
	new->next = *LCP;
	*LCP = new;
	return new;
}

CellProtected* read_protected(char* file) {
	FILE* fichier = fopen(file,"r");
    if (fichier == NULL){
        fprintf(stderr, "%s; %s; l.%d: Can't open file: %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, file);
    	exit(EXIT_FAILURE);
    }
    char buffer[512];
    char keystring[256];
    char mess[256];
    char crypted[256];
    // Création des éléments de structures pour créer un élément CellProtected
    Key* pKey = NULL;
    Signature* sgn = NULL;
    Protected* p = NULL;
    CellProtected* list = NULL;
    while(fgets(buffer, 512, fichier) != NULL){
        sscanf(buffer,"%s %s %s", keystring, mess, crypted);
        pKey = str_to_key(keystring);
        sgn = str_to_signature(crypted);
        p = init_protected(pKey,strdup(mess),sgn);
        list = inserer_en_tete_protected(&list, p);
    }
    fclose(fichier);
    return list;
}

void print_list_protected(CellProtected* LCP) {
	char* pr;
	while(LCP != NULL) {
		pr = protected_to_str(LCP->data);
		printf("%s\n", pr);
		free(pr);
		LCP = LCP->next;
	}
}

void delete_cell_protected(CellProtected* cp) {
	liberer_protected(cp->data);
	free(cp);
}

void delete_list_protected(CellProtected* LCP) {
	CellProtected* tmp;
    while (LCP != NULL){
        tmp = LCP->next;
        delete_cell_protected(LCP);
        LCP = tmp;
    }
}

void supprimeFraude(CellProtected **cp) {
    if(!(*cp)) return;
    // Supprime toutes les déclarations dont la signature n’est pas valide
    CellProtected* first = *cp;
    CellProtected* prec = first; 
    CellProtected* tmp = first->next; 
    while(tmp) {
        // Verifie si la signature n'est pas valide
        if(!(verify(tmp->data))) {
            prec->next = tmp->next; 
            delete_cell_protected(tmp);
        } else {
            prec = tmp; 
        }
        tmp = prec->next;
    }
    if(!(verify(first->data))) {
        *cp = first->next;
        delete_cell_protected(first);
    }
}

//Il faudrait une liste doublement chainee pour avoir une fusion en O(1) au lieu de O(len(votes1))
CellProtected* fusion_list_protected(CellProtected* votes1, CellProtected* votes2) {
    //si une liste est vide, la fusion c'est l'autre
    if(!votes1)
        return votes2;
    if(!votes2)
    	return votes1;
    //On parcourt votes1
    CellProtected *curr = votes1;
    while (curr->next)
        curr = curr->next;
    curr->next = votes2;
    return votes1;
}
