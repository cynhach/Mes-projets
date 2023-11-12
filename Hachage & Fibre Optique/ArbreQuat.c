#include "ArbreQuat.h"
#include "Reseau.h"

void chaineCoordMinMax(Chaines* c, double* xmin, double* ymin, double* xmax, double* ymax){
    CellChaine *tmpC;
    CellPoint *tmpP;
    // recherche des coordonnés minimal et maximal en parcourant la chaine
    for (tmpC = c->chaines; tmpC != NULL; tmpC = tmpC->suiv) {
      for (tmpP = tmpC->points; tmpP != NULL; tmpP = tmpP->suiv){
            if(tmpP->x < *xmin)
                *xmin = tmpP->x;
            else if(tmpP->x > *xmax)
                *xmax = tmpP->x;
            if(tmpP->y < *ymin)
                *ymin = tmpP->y;
            else if(tmpP->y > *ymax)
                *ymax = tmpP->y;
        }
    }
}

void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
  double tmpxc, tmpyc;

  if (n == NULL || parent == NULL)
    return;
  if (n->x < parent->xc)//a gauche de l'arbre
      tmpxc = parent->xc - parent->coteX / 4.0;
    else
      tmpxc = parent->xc + parent->coteX / 4.0;

    if (n->y < parent->yc)//en bas de l'arbre
      tmpyc = parent->yc - parent->coteY / 4.0;
    else
      tmpyc = parent->yc + parent->coteY / 4.0;

  if (*a == NULL) {
    *a = creerArbreQuat(tmpxc, tmpyc, parent->coteX / 2.0, parent->coteY / 2.0);
    (*a)->noeud = n;
    return;
  }
  if ((*a)->noeud != NULL) {
    Noeud* tmpN = (*a)->noeud;
    (*a)->noeud = NULL;

    insererNoeudArbre(tmpN, a, *a);
    insererNoeudArbre(n, a, *a);
    return;
  }
  
  if ((*a != NULL) && ((*a)->noeud == NULL)){
    if (n->x < (*a)->xc){
      if (n->y < (*a)->yc)
        insererNoeudArbre(n, &((*a)->so), *a);
    else
        insererNoeudArbre(n, &((*a)->no), *a);
    } else {
    if (n->y < (*a)->yc)
        insererNoeudArbre(n, &((*a)->se), *a);
    else
        insererNoeudArbre(n, &((*a)->ne), *a);
    }
  }
}


Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat* parent, double x, double y){

  if (*a == NULL) {//aucun noeud en (x,y). Creation:
    CellNoeud* tmpCN = ajoutCellNoeudReseau(R, x, y);
    insererNoeudArbre(tmpCN->nd, a, parent);
    return tmpCN->nd;
  } else if (((*a)->noeud != NULL)){
    if ((*a)->noeud->x == x && (*a)->noeud->y == y){
      return (*a)->noeud;
    }
    CellNoeud* tmpCN = ajoutCellNoeudReseau(R, x, y);
    insererNoeudArbre(tmpCN->nd, a, parent);
    return tmpCN->nd; 
  }
  if ((*a != NULL) && ((*a)->noeud == NULL)){
    if (x < (*a)->xc){
      if (y < (*a)->yc)
        return rechercheCreeNoeudArbre(R, &((*a)->so), *a,x,y);
    else
        return rechercheCreeNoeudArbre(R, &((*a)->no), *a,x,y);
    } else {
    if (y < (*a)->yc)
        return rechercheCreeNoeudArbre(R, &((*a)->se), *a,x,y);
    else
        return rechercheCreeNoeudArbre(R, &((*a)->ne), *a,x,y);
    }
  }
  return NULL;
}

static void getCote(Chaines* c, double* coteX, double* coteY,double* xmin, double* ymin){
  double xmax = c->chaines->points->x;
  double ymax = c->chaines->points->y;
  *xmin = xmax;
  *ymin = ymax; 
  chaineCoordMinMax(c, xmin, ymin, &xmax, &ymax);
  *coteX = xmax - *xmin;
  *coteY = ymax - *ymin;
}

Reseau* reconstitueReseauArbre(Chaines* C){
  Reseau* r = alloueReseau("reconstitueReseauArbre");
  CellCommodite* cC;
  CellChaine* tmpC;
  CellPoint* tmpP;
  Noeud* n, *nSuiv, *nPrec;
  r->nbNoeuds = 0;
  r->gamma = C->gamma;
  //si on est au premier élément de la liste alors on ne fait la maj des voisins que du suivant, sinon du suivant et précédent
  int premier = 0;
  double coteX, coteY,xmin,ymin;
  getCote(C, &coteX, &coteY, &xmin, &ymin);
  ArbreQuat* parent = creerArbreQuat(xmin + coteX / 2, ymin + coteY / 2, coteX, coteY);
  ArbreQuat** a = &parent;

  for (tmpC = C->chaines; tmpC != NULL; tmpC = tmpC->suiv) {
    cC = alloueCommodites("reconstitueReseauArbre");
    cC->extrA = rechercheCreeNoeudArbre(r, &parent, parent, tmpC->points->x, tmpC->points->y);

    for (tmpP = tmpC->points; tmpP != NULL; tmpP = tmpP->suiv){
      n = rechercheCreeNoeudArbre(r, a, parent, tmpP->x, tmpP->y);
      if (tmpP->suiv != NULL){
        nSuiv = rechercheCreeNoeudArbre(r, a, parent, tmpP->suiv->x, tmpP->suiv->y);
      }
      // mise a jour des voisins
      if (premier == 0) {
        if (tmpP->suiv != NULL)
          majVoisin(n, nSuiv);
        premier = 1;
        nPrec = n;
      } else {
        majVoisin(n, nPrec);
        majVoisin(n, nSuiv);
        nPrec = n;
      }
        nPrec = n;
    }
    premier = 0;
    cC->extrB = n;
    cC->suiv = r->commodites;
    r->commodites = cC;
  }
  //  libererArbre(parent);//leak a reparer
  return r;
}
