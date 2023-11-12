#include "SVGwriter.h" //Chaine.h y est inclut
#include "Chaine.h"

//tester toutes les fonctions de l'exercice 1
int main(int ac, char** av){
  if (ac < 2){
    printf("Usage : ./%s <Chaine_file> <nom_Instance>\n", av[0]);
    return -1;
  }
  FILE*     f = fopen(av[1],"r");
  Chaines*  c = lectureChaines(f); 
  FILE*     fr = fopen("Data.cha","w");

  ecrireChaines(c, fr);
  if (ac == 3)
    afficheChainesSVG(c, av[2]);
  else
    afficheChainesSVG(c, "nomInstanceChaine");
  printf("Fichier '%s.html' créé\n", ac == 3 ? av[2] : "nomInstanceChaine");
  printf("Longueur physique de la 1ere chaine : %.2f\n", longueurChaine(c->chaines));
  printf("Longueur physique totale des chaines : %.2f\n", longueurTotale(c));
  printf("Nombre total de points : %d\n", comptePointsTotal(c));

  liberer_Chaines(c);
  fclose(fr);
  fclose(f);
}
