#include "Reseau.h"
#include "Chaine.h"

int   nbCommodites(Reseau *R){
  int i = 0;
  CellCommodite*  k = R->commodites;

  while (k != NULL){
    i++;
    k = k->suiv;
  }
  return i;
}

int   nbLiaisons(Reseau *R){
    int cpt = 0;
    CellNoeud* v = R->noeuds, *tmp;

    while (v != NULL){
        tmp = v->nd->voisins;
        while (tmp != NULL){
            if (tmp->nd->num < v->nd->num)
                cpt++;
            tmp = tmp->suiv;
        }
        v = v->suiv;
    }
    return cpt;
}