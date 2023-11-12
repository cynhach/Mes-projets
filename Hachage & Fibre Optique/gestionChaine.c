#include "Chaine.h"

/*Creation */

CellPoint*  creer_CellPoint(double x, double y){
    CellPoint* c;

    if (!(c = malloc(sizeof(CellPoint))))
        return NULL;
    c->x = x;
    c->y = y;
    c->suiv = NULL;
    return c;
}

CellChaine*  creer_cellChaine(int num, CellPoint* points){
    CellChaine* c;

    if (!(c = malloc(sizeof(CellChaine))))
        return NULL;
    c->numero = num;
    c->points = points;
    c->suiv = NULL;
    return c;
}

Chaines*  creer_Chaines(int gamma, int nbChaines, CellChaine* chaines){
    Chaines* c;

    if (!(c = malloc(sizeof(Chaines))))
        return NULL;
    c->gamma = gamma;
    c->nbChaines = nbChaines;
    c->chaines = chaines;
    return c;
}

/* Insertion */

CellPoint*  inserer_CellPoint(CellPoint* c, double x, double y){
    CellPoint* c_new = creer_CellPoint(x, y);

    c_new->suiv = c;
    return c_new;
}

CellChaine*  inserer_CellChaine(CellChaine* c, int num, CellPoint* points){
    CellChaine* c_new = creer_cellChaine(num, points);

    c_new->suiv = c;
    return c_new;
}

/* liberation */

void    liberer_cellChaine(CellChaine* c){
    	CellChaine* tmpC = c;
	CellPoint* tmpP;

    while (c != NULL){
        while (c->points != NULL){
            tmpP = c->points;
            c->points = c->points->suiv;
	    free(tmpP);
        }
	tmpC = c;
	c = c->suiv;
        free(tmpC);
    }
}

void    liberer_Chaines(Chaines* c){
    if (c != NULL){
        liberer_cellChaine(c->chaines);
        free(c);
    }
}