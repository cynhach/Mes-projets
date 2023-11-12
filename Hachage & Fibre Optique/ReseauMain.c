#include "SVGwriter.h" //Chaine.h y est inclut
#include "Reseau.h"

//tester toutes les fonctions de l'exercice 2-3
int main(int ac, char** av){
  if (ac < 2){
    printf("Usage : ./%s <Chaine_file> <nom_Instance>\n", av[0]);
    return -1;
  }
  FILE*     f = fopen(av[1],"r");
  Chaines*  c = lectureChaines(f); 
  FILE*     fr = fopen("Data.res","w");

  Reseau* r = reconstitueReseauListe(c);
  ecrireReseau(r, fr);
  printf("Fichier 'Data.res' créé\n");
  if (ac == 3){
    afficheReseauSVG(r, av[2]);
    afficheChainesSVG(c, "nomInstanceChaine");
  }
  else{
    afficheReseauSVG(r, "nomInstanceReseau");
    afficheChainesSVG(c, "nomInstanceChaine");
  }
  printf("Fichier '%s.html' et 'nomInstanceChaine.html' créés\n", ac == 3 ? av[2] : "nomInstanceReseau");
  printf("Nombre de commodité : %d\n", nbCommodites(r));
  printf("Nombre de liaisons : %d\n", nbLiaisons(r));
  printf("Nombre de Noeuds : %d\n", r->nbNoeuds);
  
  liberer_Reseau(r);
  liberer_Chaines(c);
  fclose(fr);
  fclose(f);
}
