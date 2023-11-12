#include "Graphe.h"

//allocation sommet et informations necessaires
Sommet*     creerSommet(CellNoeud *n, int num){
    Sommet* s;

    if (!(s = malloc(sizeof(Sommet)))){
        printf("Erreur allocation : creerSommet\n");
        return NULL;
    }
    s->num = num;
    s->x = n->nd->x;
    s->y = n->nd->y;
    s->L_voisin = NULL;

    return s;
}

//parcours liste noeuds et ajout des arretes (dans un sens seulement) 
// avec u < v
Cellule_arete*  ajoutArrete(CellNoeud* n, int num){
    Cellule_arete* ar = NULL;

    for(CellNoeud* tmpN = n->nd->voisins; tmpN != NULL; tmpN = tmpN->suiv){
        if (tmpN->nd->num - 1 < num)
            ar = insererArrete(ar, tmpN->nd->num - 1, num);
    }
    return ar;
}

//cree une celluleArrete et une arrete {u,v} et l'insere en tete de L_voisin
Cellule_arete*  insererArrete(Cellule_arete* L_voisin, int u, int v){
    Cellule_arete* new;
    // printf("%d %d\n", u, v);

    if (!(new = malloc(sizeof(Cellule_arete)))){
        printf("Erreur allocation : insererArrete\n");
        return NULL;
    }
    if (!(new->a = malloc(sizeof(Arete)))){
        printf("Erreur allocation : insererArrete\n");
        return NULL;
    }
    new->a->u = u;
    new->a->v = v;
    new->suiv = L_voisin;
    return new;
}

//ajoute les arrete dans la liste des voisins u
void    majArrete(Graphe* g){

    for (int i = 0; i < g->nbsom; i++) // parcours sommets
        for (Cellule_arete* v = g->T_som[i]->L_voisin; v != NULL; v = v->suiv) //parcours liste voisins
            if (g->T_som[i]->num == v->a->v)
                g->T_som[v->a->u]->L_voisin = enteteArrete(g->T_som[v->a->u]->L_voisin, v->a);
}

// ajoute arrete en tete d'une liste de voisins sans l'allouer
Cellule_arete*  enteteArrete(Cellule_arete* tete, Arete* a){
    Cellule_arete* new;

    if (!(new = malloc(sizeof(Cellule_arete)))){
        printf("Erreur allocation : enteteArrete\n");
        return NULL;
    }
    new->a = a;
    new->suiv = tete;
    return new;
}


/* liberer memoire graphe */

void liberer_CellArete(int num, Cellule_arete* Ca){
    Cellule_arete* tmpCa;

    while (Ca != NULL){
        tmpCa = Ca;
        if (Ca->a->v == num)
            free(Ca->a);
        Ca = Ca->suiv;
        free(tmpCa);
    }
}

void    libererGraphe(Graphe *g){
    for (int i = 0; i < g->nbsom; i++){
        liberer_CellArete(i, g->T_som[i]->L_voisin);
        free(g->T_som[i]);
    }
    free(g->T_som);
    free(g->T_commod);
    free(g);
}