#include "Reseau.h"
#include "Chaine.h"
#include "SVGwriter.h"

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
  CellNoeud* tmpCellNoeud = R->noeuds;
  Noeud* tmpNoeud;
  //recherche du noeud
  while (tmpCellNoeud) { 
    tmpNoeud = tmpCellNoeud->nd;
    if (tmpNoeud->x == x && tmpNoeud->y == y)
      return tmpNoeud;
    tmpCellNoeud = tmpCellNoeud->suiv;
  }
  //aucun noeud en (x,y). Creation: 
  return ajoutNoeudReseau(R,x,y);
}

Reseau* reconstitueReseauListe(Chaines *c){
  Reseau* r = alloueReseau("reconstitueReseauListe");
  CellCommodite* cC;
  CellChaine* tmpC;
  CellPoint* tmpP;
  Noeud* n, *nSuiv, *nPrec;

  //si on est au premier élément de la liste alors on ne fait la maj des voisins que du suivant, sinon du suivant et précédent
  int premier = 0;
  r->nbNoeuds = 0;
  r->gamma = c->gamma;

  for (tmpC = c->chaines; tmpC != NULL; tmpC = tmpC->suiv) {
    cC = alloueCommodites("reconstitueReseauListe");
    cC->extrA = rechercheCreeNoeudListe(r, tmpC->points->x, tmpC->points->y);

    for (tmpP = tmpC->points; tmpP != NULL; tmpP = tmpP->suiv) {
      n = rechercheCreeNoeudListe(r, tmpP->x, tmpP->y);
      if (tmpP->suiv != NULL)
        nSuiv = rechercheCreeNoeudListe(r, tmpP->suiv->x, tmpP->suiv->y);
      // mise a jour des voisins
      if (premier == 0) {
        if (tmpP->suiv != NULL)
          majVoisin(n,nSuiv);
        premier = 1;
        nPrec = n;

      } else {
        majVoisin(n, nPrec);
        majVoisin(n, nSuiv);
        nPrec = n;
      }
    }
    premier = 0;

    cC->extrB = n;
    cC->suiv = r->commodites;
    r->commodites = cC;
  }

  return r;
}

/* ecrire */

void ecrireReseau(Reseau *R, FILE *f){
    if (R == NULL)
      return;
    CellNoeud*  v = R->noeuds, *tmp;
    CellCommodite*  k = R->commodites;

    fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
    fprintf(f, "NbLiaisons: %d\n", nbLiaisons(R));
    fprintf(f, "NbCommodites: %d\n", nbCommodites(R));
    fprintf(f, "Gamma: %d\n\n", R->gamma);

    while (v != NULL){
        fprintf(f, "v %d %f %f\n", v->nd->num, v->nd->x, v->nd->y);
        v = v->suiv;
    }
    fprintf(f, "\n");
    v = R->noeuds;//retourne au debut de la chaine de noeuds
    while (v != NULL){
        tmp = v->nd->voisins;
        while (tmp != NULL){
            if (tmp->nd->num < v->nd->num)
                fprintf(f, "l %d %d\n", tmp->nd->num, v->nd->num);
            tmp = tmp->suiv;
        }
        v = v->suiv;
    }

    fprintf(f, "\n");
    while (k != NULL){
        fprintf(f, "k %d %d\n", k->extrA->num, k->extrB->num);
        k = k->suiv;
    }
}


/* affichage */

void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN, *courv;
    SVGwriter svg;
    double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;

    courN = R->noeuds;
    while (courN != NULL){
        if (maxx < courN->nd->x) maxx = courN->nd->x;
        if (maxy < courN->nd->y) maxy = courN->nd->y;
        if (minx > courN->nd->x) minx = courN->nd->x;
        if (miny > courN->nd->y) miny = courN->nd->y;
        courN = courN->suiv;
    }
    SVGinit(&svg, nomInstance, 500, 500);
    courN = R->noeuds;
    while (courN != NULL){
        SVGlineRandColor(&svg);
        SVGpoint(&svg, 500 * (courN->nd->x - minx) / (maxx - minx), 500 * (courN->nd->y - miny) / (maxy - miny));
        courv = courN->nd->voisins;
        while (courv != NULL){
            if (courv->nd->num < courN->nd->num)
                SVGline(&svg, 500 * (courv->nd->x - minx) / (maxx - minx), 500 * (courv->nd->y - miny) / (maxy - miny), 500 * (courN->nd->x - minx) / (maxx - minx), 500 * (courN->nd->y - miny) / (maxy - miny));
            courv = courv->suiv;
        }
        courN = courN->suiv;
    }
    SVGfinalize(&svg);
}
