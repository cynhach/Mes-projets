#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "Graphe.h"
#define TEST 3
#define TEST1 3
#define TEST2 4

void  testEcritureReseau(Reseau *r){
  FILE*     fr = fopen("Reconstitue.res","w");

  if (fr == NULL)
    return;
  ecrireReseau(r, fr);
  fclose(fr);
}

void propChaine(Chaines *c){
  printf("Longueur physique de la 1ere chaine : %.2f\n", longueurChaine(c->chaines));
  printf("Longueur physique totale des chaines : %.2f\n", longueurTotale(c));
  printf("Nombre total de points : %d\n", comptePointsTotal(c));
}

void propReseau(Reseau *r){
  printf("Nombre de commodité : %d\n", nbCommodites(r));
  printf("Nombre de liaisons : %d\n", nbLiaisons(r));
  printf("Nombre de Noeuds : %d\n", r->nbNoeuds);
}

void afficheArrete(Graphe* g){
  printf("Affichage des arrete de g :\n(gamma = %d) (nbcommod = %d) (nbsom =%d)\n", g->gamma, g->nbcommod, g->nbsom);
  for(int i = 0; i < g->nbsom; i++){
    printf("Sommet %d\n", i);
    for (Cellule_arete* tmpC = g->T_som[i]->L_voisin; tmpC != NULL; tmpC = tmpC->suiv)
      printf("%d %d \n", tmpC->a->u, tmpC->a->v);
  }
}

void    afficheCommodite(Graphe* g){
  ListeEntier* L;

  printf("Affichage des commodites de g et leur chemin le plus court:\n(gamma = %d) (nbcommod = %d) (nbsom =%d)\n", g->gamma, g->nbcommod, g->nbsom);
  for (int i = 0; i < g->nbcommod; i++){
    printf("\n\nCommodité %d : {%d, %d} = %d\nChemin : ", i, g->T_commod[i].e1, g->T_commod[i].e2, tailleCheminCourt(g, g->T_commod[i].e1, g->T_commod[i].e2));
    L = cheminCourt(g, g->T_commod[i].e1, g->T_commod[i].e2);
    for (ListeEntier c = *L; c != NULL; c = c->suiv)
      printf("%d ", c->u);
    desalloue(L);
    free(L);
  }
}

void  testCheminCommod(Graphe *g, int c){
  printf("\n\nChemin le plus court entre {%d, %d} de taille %d\n", g->T_commod[c].e1, g->T_commod[c].e2, tailleCheminCourt(g, g->T_commod[c].e1, g->T_commod[c].e2));
  ListeEntier* L = cheminCourt(g, g->T_commod[c].e1, g->T_commod[c].e2);
  for (ListeEntier c = *L; c != NULL; c = c->suiv)
    printf("%d ", c->u);
  desalloue(L);
  free(L);
}

void  testChemin(Graphe *g, int u, int v){
  printf("\n\nChemin le plus court entre {%d, %d} de taille %d\n", u, v, tailleCheminCourt(g, u, v));
  ListeEntier* L = cheminCourt(g, u, v);
  for (ListeEntier c = *L; c != NULL; c = c->suiv)
    printf("%d ", c->u);
  desalloue(L);
  free(L);
}