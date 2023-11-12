#include "Chaine.h"

double longueurChaine(CellChaine *c){
  double      res = 0;
  CellChaine* tmp = c;
  CellPoint*  tmpPointsA, *tmpPointsB;

  while (tmp){
    tmpPointsA = c->points;

    while (tmpPointsA->suiv) {
      tmpPointsB = tmpPointsA->suiv;
      res += sqrt((tmpPointsB->x - tmpPointsA->x) * (tmpPointsB->x - tmpPointsA->x) + (tmpPointsB->y - tmpPointsA->y) * (tmpPointsB->y - tmpPointsA->y));
      tmpPointsA = tmpPointsA->suiv;
    }
    tmp = tmp->suiv;
  }

  return res;
}

double longueurTotale(Chaines *c){
  double      res = 0.0;
  CellChaine* tmp = c->chaines;

  while (tmp) {
    res += longueurChaine(tmp);
    tmp = tmp->suiv;
  }

  return res;
}

int comptePointsTotal(Chaines *c){
  int res = 0;
  CellChaine* tmpCellChaine = c->chaines;
  CellPoint* tmpCellPoint;

  while  (tmpCellChaine) {
    tmpCellPoint = tmpCellChaine->points;

    while (tmpCellPoint) {
      res++;
      tmpCellPoint = tmpCellPoint->suiv;
    }

    tmpCellChaine = tmpCellChaine->suiv;
  }
  return res;
}

/*int main()
{
    //test 3 dernieres fonctions
    CellPoint* p1 = creer_CellPoint(1, 2);
    CellPoint* p2 = creer_CellPoint(2, 3);
    CellPoint* p3 = creer_CellPoint(3, 4);
    CellPoint* p4 = creer_CellPoint(1, 2);
    CellPoint* p5 = creer_CellPoint(2, 3);
    CellPoint* p6 = creer_CellPoint(3, 4);
    p1->suiv = p2;
    p2->suiv = p3;
    p3->suiv = p4;
    p4->suiv=p5;
    p5->suiv=p6;
    CellChaine* c = creer_cellChaine(0,p1);
    CellChaine* c2 = creer_cellChaine(0,p5);

    double d = longueurChaine(c);

    Chaines* chaine = creer_Chaines(5,3,c);

    int a = comptePointsTotal(chaine);
    liberer_cellChaine(c);
    printf("%f , %d",d,a);
    return 0;
}*/

/*
int main(int ac, char** av){//main pour tester les fonctions de chaine
  FILE*   f = fopen(av[1],"r");
  Chaines* c = lectureChaines(f);
  double  a = longueurTotale(c);
  int     b = comptePointsTotal(c);

  printf("%f, %d",a,b);
  liberer_Chaines(c);
  fclose(f);
}*/
