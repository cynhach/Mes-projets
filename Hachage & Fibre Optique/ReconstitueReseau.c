#include "Reseau.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "Graphe.h"
#include "testFunction.h"



//return -1 si les arguments en ligne de commande ne sont pas valide
//return numero associé a une structure sinon
static Chaines*  check_args(int ac, char **av, int* typeStruc){
  Chaines* c = NULL;
  *typeStruc = -1;

  if (ac != 3)
    printf("Error : Nombre args Invalide.\nUsage %s <nomFichier.cha> <type_struct = [1-3]>\n", av[0]);
  else if (strcmp(av[1] + strlen(av[1]) - 4, ".cha") != 0)
    printf("Error : Nom fichier Invalide (.cha).\nUsage %s <nomFichier.cha> <type_struct = [1-3]>\n", av[0]);
  else if (atoi(av[2]) < 1 || atoi(av[2]) > 3 )
    printf("Error : Numero type Structure Invalide (1-3).\nUsage %s <nomFichier.cha> <type_struct = [1-3]>\n", av[0]);
  else{
    *typeStruc = atoi(av[2]);
    FILE *f = fopen(av[1], "r"); 
    if (f == NULL){
      printf("Error : Ouverture de fichier %s raté", av[1]);
      return NULL;
    }
    c = lectureChaines(f);
    fclose(f);
  }
  return c;
}


int main(int ac, char** av){
  int typeStruc;
  Chaines *c = NULL;

  if ((c = check_args(ac, av, &typeStruc)) == NULL)
    return -1;
  Reseau *r = NULL;

  switch (typeStruc){
  case 1:
    printf("Reconstitution Reseau avec methode : Liste\n");
    r = reconstitueReseauListe(c);
    break;
  
  case 2:
    printf("Reconstitution Reseau avec methode : Table de Hachage\n");
    r = reconstitueReseauHachage(c, 5);
    break;

  case 3:
    printf("Reconstitution Reseau avec methode : Arbre\n");
    r = reconstitueReseauArbre(c);
    break;

  default:
    break;
  }

/* commenter pour ne plus afficher les proprietes */
  propChaine(c);
  propReseau(r);

/* decommenter pour creer les fichiers SVG */
  // afficheReseauSVG(r, "nomInstanceReseau");
  // afficheChainesSVG(c, "nomInstanceChaine");

/* Partie Optimisation du reseau */
  Graphe* g  = creerGraphe(r);
  
  // afficheArrete(g);
  // afficheCommodite(g);
  // testChemin(g, 7, 11);
  // testCheminCommod(g, 0);
  // printf("Reorganise : %s\n", reorganiseReseau(r) == 1 ? "Vrai" : "Faux");
  

  libererGraphe(g);
  liberer_Chaines(c);
  liberer_Reseau(r);
}
