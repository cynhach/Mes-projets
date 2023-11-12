#include "Chaine.h"
#include "SVGwriter.h"

// permet de lire les points d'une ligne
static CellPoint*  lire_points(char* ligne, int nbP){//lit les nbP points d'une chaine
  CellPoint* c = NULL;
  double  x, y;
  int     i = 0;
  int     cpt = 0; // compte espace pour avancer dans ligne

  while (ligne[i] && nbP > 0){
    cpt = 0;
    while (ligne[i] && cpt != 2){//avance jusqu'au prochain point
      if (ligne[i] == ' ')
        cpt++;
      i++;
    }
    if (sscanf(ligne + i, "%lf %lf", &x, &y) != 2){//recupere coordonnee 1e point
      printf("Erreur lecture : lire_points\n");
      return NULL;
    }
    c = inserer_CellPoint(c, x, y);
    nbP--;
  }
  return c;
}

Chaines*    lectureChaines(FILE *f){
    char    ligne[10001];
    int     nbChain,nbChaines;
    int     gamma;
    int     numChaine;
    int     nbPoints;
    CellChaine* cellChain = NULL;
    Chaines*    c = NULL;

    fgets(ligne, 10000, f);
    if (sscanf(ligne, "NbChain: %d", &nbChain) != 1){
        printf("Erreur lecture : lectureChaines - NbChain\n");
        return NULL;
    }
    nbChaines = nbChain;
    fgets(ligne, 10000, f);
    if (sscanf(ligne, "Gamma: %d", &gamma) != 1){
        printf("Erreur lecture : lectureChaines - Gamma\n");
        return NULL;
    }

    while (fgets(ligne, 10000, f) && nbChain > 0){//recupere les nbChaine
      while (*ligne == '\n') {
        fgets(ligne, 10000, f);
      }
        if (sscanf(ligne, "%d %d", &numChaine, &nbPoints) != 2){
            printf("Erreur lecture : lectureChaines - ligne\n");
            return NULL;
        }
        cellChain = inserer_CellChaine(cellChain, numChaine, lire_points(ligne, nbPoints));
        nbChain--;
    }
    c = creer_Chaines(gamma, nbChaines, cellChain);
    return c;
}


void ecrireChaines(Chaines *c, FILE *f){
    CellChaine* tmpChaine = c->chaines;
    CellPoint*  tmpPoints;
    int nbPoints = 1;

    fprintf(f, "NbChain: %d\nGamma: %d\n\n", c->nbChaines, c->gamma);

    while (tmpChaine) {
        tmpPoints = tmpChaine->points;
        fprintf(f, "%d ", tmpChaine->numero);

        for(tmpPoints = tmpChaine->points; tmpPoints; tmpPoints = tmpPoints->suiv)
            nbPoints++;
        fprintf(f, "%d ", nbPoints);

        for(tmpPoints = tmpChaine->points; tmpPoints; tmpPoints = tmpPoints->suiv)
            fprintf(f, "%.2f %.2f ", tmpPoints->x, tmpPoints->y);
        fputs("\n", f);

        nbPoints = 1;
        tmpChaine = tmpChaine->suiv;
    }
}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    double maxx = 0, maxy = 0, minx = 1e6, miny = 1e6;
    double precx, precy;
    CellChaine  *ccour;
    CellPoint   *pcour;
    SVGwriter   svg;

    ccour = C->chaines;
    while (ccour != NULL){
        pcour = ccour->points;
        while (pcour != NULL){
            if (maxx < pcour->x) maxx = pcour->x;
            if (maxy < pcour->y) maxy = pcour->y;
            if (minx > pcour->x) minx = pcour->x;
            if (miny > pcour->y) miny = pcour->y;  
            pcour = pcour->suiv;
        }
    ccour = ccour->suiv;
    }
    SVGinit(&svg, nomInstance, 500, 500);
    ccour = C->chaines;
    while (ccour != NULL){
        pcour = ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg, 500 * (pcour->x - minx) / (maxx - minx), 500 * (pcour->y - miny) / (maxy - miny)); 
        precx = pcour->x;
        precy = pcour->y;  
        pcour = pcour->suiv;
        while (pcour != NULL){
            SVGline(&svg, 500 * (precx - minx) / (maxx - minx), 500 * (precy - miny) / (maxy - miny), 500 * (pcour->x - minx) / (maxx - minx), 500 * (pcour->y - miny) / (maxy - miny));
            SVGpoint(&svg, 500 * (pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx = pcour->x;
            precy = pcour->y;    
            pcour = pcour->suiv;
        }
        ccour = ccour->suiv;
    }
    SVGfinalize(&svg);
}

Chaines*  generationAleatoire(int nbChaines, int nbPointsChaine, int xmax, int ymax){
    CellChaine* cellChain = NULL;
    CellPoint* cellPoint = NULL;
    Chaines*    c = NULL;

    for (int numChaine = 0; numChaine < nbChaines; numChaine++){
        cellPoint = NULL;
        for (int i = 0; i < nbPointsChaine; i++){
            cellPoint = inserer_CellPoint(cellPoint, rand() % xmax, rand() % ymax);
        }
        cellChain = inserer_CellChaine(cellChain, numChaine, cellPoint);
    }
    c = creer_Chaines(nbPointsChaine, nbChaines, cellChain);
    return c;
}