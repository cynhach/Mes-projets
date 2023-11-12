#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "Graphe.h"

/* testFunction.c */

void    testEcritureReseau(Reseau *r); // ecrit le reseau dans un fichier "Reconstitue.res"
void    propChaine(Chaines *c); //affiche les propriété de la chaine lu
void    propReseau(Reseau *r); //affiche les propriété du reseau reconstitué
void    afficheArrete(Graphe* g); //affiche toutes les arretes d'un Graphe
void    afficheCommodite(Graphe* g); //affiche toutes les commodite d'un Graphe
void    testCheminCommod(Graphe *g, int c); // affiche chemin le plus court de commodite c
void  testChemin(Graphe *g, int u, int v); // affiche chemin le plus court entre u et v

#endif