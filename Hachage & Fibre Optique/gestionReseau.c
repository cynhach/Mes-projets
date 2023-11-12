#include "Reseau.h"

/*Creation Noeud */

Noeud*  creerNoeud(int num, double x, double y){
  Noeud*  v;

  if (!(v = malloc(sizeof(Noeud)))) {
    printf("Erreur allocation : creerNoeud\n");
    return NULL;
  }
  v->num = num;
  v->x = x;
  v->y = y;
  v->voisins = NULL;

  return v;
}

Noeud*   ajoutNoeudReseau(Reseau* R, double x, double y){
  CellNoeud* tmpCN = alloueCellNoeud("ajoutNoeudReseau");
  R->nbNoeuds++;
  tmpCN->nd = creerNoeud(R->nbNoeuds, x, y);

  tmpCN->suiv = R->noeuds;
  R->noeuds = tmpCN;
  return tmpCN->nd;
}

/*Allocation */

CellCommodite* alloueCommodites(char *message){
  CellCommodite* c = malloc(sizeof(CellCommodite));

  if (c == NULL){
    printf("Erreur d'allocation : Commodité - %s\n", message);
    return NULL;
  }

  c->extrA = NULL;
  c->extrB = NULL;
  c->suiv = NULL;

  return c;
}

Reseau* alloueReseau(char *message){
  Reseau* r = malloc(sizeof(Reseau));

  if (r == NULL){
    printf("Erreur d'allocation : Reseau - %s\n", message);
    return NULL;
  }

  r->nbNoeuds = 0;
  r->gamma = 0;
  r->noeuds = NULL;
  r->commodites = NULL;

  return r;
}

CellNoeud* alloueCellNoeud(char *message){
  CellNoeud* c = malloc(sizeof(CellNoeud));

  if (c == NULL){
    printf("Erreur d'allocation : CellNoeud - %s\n", message);
    return NULL;
  }
  c->nd = NULL;
  c->suiv = NULL;
  return c;
}


/* Liberer */


void    liberer_Reseau(Reseau* r){
  CellNoeud* tmpN = r->noeuds;
  CellNoeud* tmpV;
  CellNoeud* tmpNsupp;

  while (tmpN) {
    tmpV = tmpN->nd->voisins;
    while (tmpV) {
      tmpNsupp = tmpV;
      tmpV = tmpV->suiv;
      free(tmpNsupp);

    }
    tmpNsupp = tmpN;
    tmpN = tmpN->suiv;
    free(tmpNsupp->nd);
    free(tmpNsupp);
  }

  CellCommodite* tmpC = r->commodites;
  CellCommodite* tmpCsupp;
  while (tmpC) {
    tmpCsupp = tmpC;
    tmpC = tmpC->suiv;
    free(tmpCsupp);
  }
  free(r);
}

/*Mise a jour Reseau */

void majVoisin(Noeud* n, Noeud* nvoisin){
  if (nvoisin == NULL)
    return;

  CellNoeud* cellNtmp = n->voisins;
  Noeud* voisin;

  //recherche potentiel voisins
  while (cellNtmp) {
    voisin = cellNtmp->nd;
    if (nvoisin->x == voisin->x && nvoisin->y == voisin->y)
      return;
    cellNtmp = cellNtmp->suiv;
  }

  //ajout du voisin
  cellNtmp = alloueCellNoeud("majVoisin");
  cellNtmp->nd = nvoisin;
  cellNtmp->suiv = n->voisins;
  n->voisins = cellNtmp;
}
