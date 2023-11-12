#ifndef HACHAGE_H
#define HACHAGE_H

#include "Reseau.h"

typedef struct s_tableHachage{
    int nbE;/*nombre d’elements contenus dans la table de hachage */
    int   m; /*taille de la table de hachage */
    CellNoeud** noeuds;        
}   TableHachage;

/* Hachage.c */
int             fonctionClef(double x, double y);
int             fonctionHachage(int cle, int m);
int             fonctionClef2(double x, double y);
TableHachage*   creerTable(int m);
Noeud*          rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y);
Reseau*         reconstitueReseauHachage(Chaines *C, int M);
void            freeHachage(TableHachage *t);

#endif