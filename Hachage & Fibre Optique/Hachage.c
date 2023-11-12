#include "Hachage.h"
#include "Reseau.h"

/* convertie x et y en clef */
int     fonctionClef(double x, double y){
    return (int)(y + (x + y)*(x + y + 1) / 2);
}

int     fonctionHachage(int cle, int m){
  double a = (sqrt(5) - 1) / 2;
  return (m * (cle * a - (int)(cle * a)));
}

/* création de la table de Hachage */
TableHachage* creerTable(int m){
  TableHachage* t;
  if (!(t = malloc(sizeof(TableHachage)))){
    printf("Erreur d'allocation : creerTable\n");
    return NULL;
  }
  t->m = m;
  t->nbE = 0;

  CellNoeud** c = malloc(m * sizeof(CellNoeud*));
  for(int i = 0 ; i < m ; i++){
    c[i] = NULL;
  }
  t->noeuds = c;
  return t;
}

/* liberer Table de Hachage */

void freeHachage(TableHachage *t){
  CellNoeud** tmpN = t->noeuds;
  CellNoeud* tmpNs;
  CellNoeud* tmpNsupp;
  for (int i = 0; i < t->m; i++) {
    tmpNs = tmpN[i] ;
    while (tmpNs) {
      tmpNsupp = tmpNs;
      tmpNs = tmpNs->suiv;
      free(tmpNsupp);
    }
  }
  free(t->noeuds);
  free(t);
}

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage*H, double x, double y){
  int index = fonctionHachage(fonctionClef(x,y),H->m);
  CellNoeud* tmpCellNoeud = H->noeuds[index];

  //recherche du noeud potentiel
  while(tmpCellNoeud){
    if (tmpCellNoeud->nd->x == x && tmpCellNoeud->nd->y == y)
      return tmpCellNoeud->nd;
    tmpCellNoeud = tmpCellNoeud->suiv;
  }

  H->nbE++;
  R->nbNoeuds++;

  // création des noeuds a ajouter (table + reseau)
  Noeud* n = creerNoeud(R->nbNoeuds, x, y);
  // Noeud* nH = creerNoeud(R->nbNoeuds, x, y);
  tmpCellNoeud = alloueCellNoeud("rechercheCreeNoeudHachage");
  CellNoeud* tmpCH = alloueCellNoeud("rechercheCreeNoeudHachage");

  //ajout du noeud dans le réseau
  tmpCellNoeud->nd = n;
  tmpCellNoeud->suiv = R->noeuds;
  R->noeuds = tmpCellNoeud;

  //ajout du noeud dans la table
  tmpCH->nd = n;
  tmpCH->suiv = H->noeuds[index];
  H->noeuds[index] = tmpCH;

  return n;
}

/* Reconstitue */

Reseau* reconstitueReseauHachage(Chaines *C, int M){
  Reseau* r = alloueReseau("reconstitueReseauHachage");
  CellCommodite* cC;
  TableHachage* t = creerTable(M);
  CellPoint* tmpP;
  Noeud* n,*nSuiv,*nPrec;
  r->nbNoeuds = 0;
  r->gamma = C->gamma;
  int premier = 0;

  for (CellChaine* tmpC = C->chaines; tmpC != NULL; tmpC = tmpC->suiv) {
    cC = alloueCommodites("reconstitueReseauHachage");
    cC->extrA = rechercheCreeNoeudHachage(r, t, tmpC->points->x, tmpC->points->y);

    for (tmpP = tmpC->points; tmpP != NULL; tmpP = tmpP->suiv) {
      n = rechercheCreeNoeudHachage(r, t, tmpP->x, tmpP->y);
      if (tmpP->suiv != NULL)
        nSuiv = rechercheCreeNoeudHachage(r, t, tmpP->suiv->x, tmpP->suiv->y);
      if (premier == 0) {
        if (tmpP->suiv != NULL)
          majVoisin(n,nSuiv);
        premier = 1;
        nPrec = n;

      } else {
        majVoisin(n,nPrec);
        majVoisin(n,nSuiv);
        nPrec = n;
      }
    }
    premier = 0;

    cC->extrB = n;
    cC->suiv = r->commodites;
    r->commodites = cC;
  }
  freeHachage(t);
  return r;
}
