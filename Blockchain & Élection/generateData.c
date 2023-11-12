#include "generateData.h"

void generate_random_data(int nv, int nc) {
	// Génère nv couples de clés (publique, secrète)
    Key keyCouple[nv][2];
    for(int i = 0; i < nv; i++){
    	init_pair_keys(&keyCouple[i][0], &keyCouple[i][1], 3, 7);
        for(int j = 0; j < i; j++){
        	// S'assure que tous les couples sont differents les uns des autres
        	if((keyCouple[i][0].val == keyCouple[j][0].val && keyCouple[i][0].n == keyCouple[j][0].n) || (keyCouple[i][1].val == keyCouple[j][1].val && keyCouple[i][1].n == keyCouple[j][1].n)){
				i--;
                continue;
			}
		}
	}
    
    // Fichier keys.txt contenant tous les couples de clés
    FILE* file1 = fopen("keys.txt","w");
	for(int i = 0;i < nv;i++){
		fprintf(file1, "%s %s\n", key_to_str(&keyCouple[i][0]), key_to_str(&keyCouple[i][1]));
	}
	fclose(file1);
	
	// Selectionne nc clés publiques aleatoirement pour définir les nc candidats
	Key candidats[nc][2];
	int random[nc];
	for(int i = 0; i < nc; i++){
		random[i] = rand()%nv;
		for(int j = 0; j < i; j++){
			if(random[j] == random[i]){
				i--;
				continue;
			}
		}
		candidats[i][0].val = keyCouple[random[i]][0].val;
		candidats[i][1].val = keyCouple[random[i]][1].val;
		candidats[i][0].n = keyCouple[random[i]][0].n;
		candidats[i][1].n = keyCouple[random[i]][1].n;
	}
	
    // Fichier candidates.txt contenant la cle publique de tous les candidats
	FILE* file2 = fopen("candidates.txt","w");
	for(int i = 0; i < nc;i++){
		fprintf(file2, "%s %s\n", key_to_str(&candidats[i][0]),key_to_str(&candidats[i][1]));
	}
	fclose(file2);
	
    // Genere une déclaration de vote signée pour chaque citoyen 
	Protected* vote[nv];
	int candidrand;
	for(int i = 0;i <nv;i++){
		candidrand = rand()%nc;
		vote[i] = init_protected(&keyCouple[i][0], key_to_str(&candidats[candidrand][0]), sign(key_to_str(&candidats[candidrand][0]), &keyCouple[i][1]));
	}
	
    // Fichier declarations.txt contenant toutes les déclarations signées
	FILE* file3 = fopen("declarations.txt","w");
	for(int i = 0; i < nv; i++){
		fprintf(file1, "%s\n", protected_to_str(vote[i]));
	}
	fclose(file3);
}
