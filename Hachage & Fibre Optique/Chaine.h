#ifndef __CHAINE_H__
#define __CHAINE_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/* Liste chainee de points */
typedef struct cellPoint{
  double x, y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
}       CellPoint;

/* Cellule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int       numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
}       CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
}       Chaines;

/* gestionChaine.c */
CellPoint*  creer_CellPoint(double x, double y);
CellChaine* creer_cellChaine(int num, CellPoint* points);
Chaines*    creer_Chaines(int gamma, int nbChaines, CellChaine* chaines);
CellPoint*  inserer_CellPoint(CellPoint* c, double x, double y);
CellChaine* inserer_CellChaine(CellChaine* c, int num, CellPoint* points);
void        liberer_cellChaine(CellChaine* c);
void        liberer_Chaines(Chaines* c);

/* Chaine.c */
Chaines*  lectureChaines(FILE *f);
void      ecrireChaines(Chaines *c, FILE *f);
void      afficheChainesSVG(Chaines *c, char* nomInstance);
Chaines*  generationAleatoire(int nbChaines,int nbPointsChaine,int xmax, int ymax);

/* mesureChaine.c */
double    longueurChaine(CellChaine *c);
double    longueurTotale(Chaines *c);
int       comptePointsTotal(Chaines *c);

#endif
