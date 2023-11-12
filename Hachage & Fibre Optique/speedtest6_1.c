#include <limits.h>
#include <time.h>
#include "Hachage.h"
#include "Reseau.h"
#include "Chaine.h"
#include "ArbreQuat.h"

int main(int argc, char **argv){
  if ( argc != 2 ){
    printf("Erreur format %s (taille table de hachage)\n",argv[0]);
    return 1;
  }

  FILE* f = fopen("./files/00014_burma.cha","r");
  Chaines* c = lectureChaines(f);


  unsigned long temps_initial_list;
  unsigned long temps_final_list;
  double temps_cpu_list;
  Reseau* reseauList;

  unsigned long temps_initial_hachage;
  unsigned long temps_final_hachage;
  double temps_cpu_hachage;
  Reseau* reaseauHachage;

  unsigned long temps_initial_Arbre;
  unsigned long temps_final_Arbre;
  double temps_cpu_Arbre;
  Reseau* reseauArbre;
  printf("list hachage arbre \n");
  for(int i = 1 ; i < 11; i++){
    temps_initial_list = clock();
    reseauList = reconstitueReseauListe(c);
    temps_final_list = clock();
    temps_cpu_list = ((double) (temps_final_list - temps_initial_list)) / CLOCKS_PER_SEC;



    temps_initial_hachage = clock();
    reaseauHachage = reconstitueReseauHachage(c ,atoi(argv[1]));
    temps_final_hachage = clock();
    temps_cpu_hachage =  ((double) (temps_final_hachage - temps_initial_hachage)) / CLOCKS_PER_SEC;



    temps_initial_Arbre = clock();
    reseauArbre = reconstitueReseauArbre(c);
    temps_final_Arbre = clock();
    temps_cpu_Arbre = ((double) (temps_final_Arbre - temps_initial_Arbre)) / CLOCKS_PER_SEC;


    printf("%f %f %f \n",temps_cpu_list, temps_cpu_hachage, temps_cpu_Arbre);

    liberer_Reseau(reseauList);
    liberer_Reseau(reaseauHachage);
    liberer_Reseau(reseauArbre);
  }

  liberer_Chaines(c);

  fclose(f);
  return 0;
}
