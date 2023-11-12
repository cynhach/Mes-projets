#include "Graphe.h"

/* Creation Graphe */

Graphe*     creerGraphe(Reseau* r){
    Graphe *g;

    if (!(g = malloc(sizeof(Graphe)))){
        printf("Erreur allocation : creerGraphe\n");
        return NULL;
    }
    g->gamma = r->gamma;
    g->nbcommod = 0;
    g->nbsom = 0;
    if (!(g->T_commod = malloc(sizeof(Commod) * nbCommodites(r)))){
        printf("Erreur allocation : creerGraphe\n");
        return NULL;
    }
    if (!(g->T_som = malloc(sizeof(Sommet) * r->nbNoeuds))){
        printf("Erreur allocation : creerGraphe\n");
        return NULL;
    }
    //creation des sommet avec liste voisins vide
    for (CellNoeud *n = r->noeuds; n != NULL; n = n->suiv){
        g->T_som[n->nd->num - 1] = creerSommet(n, n->nd->num - 1);
        g->nbsom++;
    }

    //creation des commodités
    for (CellCommodite *c = r->commodites; c != NULL; c = c->suiv){
        g->T_commod[g->nbcommod].e1 = c->extrA->num - 1;
        g->T_commod[g->nbcommod].e2 = c->extrB->num - 1;
        g->nbcommod++;
    }

    //creation liste de voisins avec arretes des sommets v
    for (CellNoeud *n = r->noeuds; n != NULL; n = n->suiv)
        g->T_som[n->nd->num - 1]->L_voisin = ajoutArrete(n, n->nd->num - 1);
    majArrete(g); //ajouts des arretes dans liste des sommets u 
    return g;
}

/* 7.2 calcule chemin le plus court entre u et v */

/* libere la file */
static void  liberer_file(S_file *f){
    if (f == NULL)
        return;
    while(!estFileVide(f))
        defile(f);
    free(f);
}

int             tailleCheminCourt(Graphe* g, int u, int v){
    if (g == NULL)
        return -1;
    if (u == v)
        return 0;   
    int visit[g->nbsom], D[g->nbsom];//on fait un tableau statique
    for (int i = 0; i < g->nbsom; i++){
        visit[i] = 0;
        D[i] = 0;
    }
    visit[u] = 1;
    S_file* F;
    if (!(F = malloc(sizeof(S_file)))){
        printf("Erreur allocation : tailleCheminCourt\n");
        return -1;
    }
    Init_file(F);
    enfile(F, u);
    int curU, curV;

    while (!estFileVide(F)){
        curU = defile(F);
        // printf("%d ", curU);

        Cellule_arete* curA = g->T_som[curU]->L_voisin;
        while (curA != NULL){
            if (curA->a->v == curU)
                curV = curA->a->u;
            else 
                curV = curA->a->v;
            if (visit[curV] == 0){
                visit[curV] = 1;
                D[curV] = D[curU] + 1;
                if (curV == v){
                    liberer_file(F);
                    return (D[curV]);
                }
                enfile(F, curV);
            }
            curA = curA->suiv;
        }
    }
    if (F != NULL)
        free(F);
    return -1; //aucun chemin existant
}


ListeEntier*    getChaine(int size, int mat[size][size], int *D,  int u, int v){
    ListeEntier*  L = malloc(sizeof(ListeEntier));
    int next = v;
    Init_Liste(L);  

    ajoute_en_tete(L, v);
    for (int cpt = D[v]; cpt > 0; cpt--){
        for(int i = 0; i < size; i++){
            if (D[i] == cpt && (mat[i][next] == 1 || mat[next][i] == 1)){
                ajoute_en_tete(L, i);
                next = i;
                break;
            }
        }
    }
    ajoute_en_tete(L, u);
    return L;
} 

ListeEntier*        cheminCourt(Graphe* g, int u, int v){
    if (g == NULL)
        return NULL;  
    int visit[g->nbsom], D[g->nbsom];//on fait un tableau statique
    int  matriceAr[g->nbsom][g->nbsom];
    for (int i = 0; i < g->nbsom; i++)
        for (int j = 0; j < g->nbsom; j++) 
            matriceAr[i][j] = 0;
    for (int i = 0; i < g->nbsom; i++){
        visit[i] = 0;
        D[i] = 0;
    }
    visit[u] = 1;
    S_file* F;
    if (!(F = malloc(sizeof(S_file)))){
        printf("Erreur allocation : tailleCheminCourt\n");
        return NULL;
    }
    Init_file(F);
    enfile(F, u);
    int curU, curV;

    while (!estFileVide(F)){
        curU = defile(F);
        // printf("%d ", curU);

        Cellule_arete* curA = g->T_som[curU]->L_voisin;
        while (curA != NULL){
            if (curA->a->v == curU)
                curV = curA->a->u;
            else 
                curV = curA->a->v;
            if (visit[curV] == 0){
                visit[curV] = 1;
                D[curV] = D[curU] + 1;
                matriceAr[curU][curV] = 1;
                if (curV == v){
                    liberer_file(F);
                    return (getChaine(g->nbsom, matriceAr, D, u, v));
                }
                enfile(F, curV);
            }
            curA = curA->suiv;
        }
    }
    if (F != NULL)
        free(F);
    return NULL; //aucun chemin existant
}


//retourne 1 si le nombre de chaınes qui passe par cette arete est inferieur a γ,
//0 sinon
//et met a jour la matrice des passage par cette arrete
int     majMatrice(int size, int gamma, int mat[size][size], ListeEntier* L){
    for (ListeEntier tmpL = *L; tmpL != NULL; tmpL = tmpL->suiv){
        if (tmpL->suiv == NULL)
            return 1;
        mat[tmpL->u][tmpL->suiv->u]++;
        if ((mat[tmpL->u][tmpL->suiv->u] + mat[tmpL->suiv->u][tmpL->u]) > gamma)
            return 0;
    }
    return 1;
}

int reorganiseReseau(Reseau* r){
    Graphe* g = creerGraphe(r); 
    int  matriceAr[g->nbsom][g->nbsom];
    int ret = 1;
    ListeEntier* L;

    for (int i = 0; i < g->nbsom; i++)
        for (int j = 0; j < g->nbsom; j++) 
            matriceAr[i][j] = 0;

    // printf("Calcul plus courte chaines entre commodités {u, v} : \n");
    for (int i = 0; i < g->nbcommod; i++){
        // printf("\n\nCommodité %d : {%d, %d} = %d\n", i, g->T_commod[i].e1, g->T_commod[i].e2, tailleCheminCourt(g, g->T_commod[i].e1, g->T_commod[i].e2));
	    L = cheminCourt(g, g->T_commod[i].e1, g->T_commod[i].e2);
        if (majMatrice(g->nbsom, g->gamma, matriceAr, L) == 0){
            desalloue(L);
            free(L);
            ret = 0;
	    break;
        }
        desalloue(L);
        free(L);
    }
    libererGraphe(g);
    return ret;
}
