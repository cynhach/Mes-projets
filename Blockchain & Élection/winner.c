#include "hash.h"
#include "key.h"

// Hypothese : decl contient une liste de déclarations avec signatures valides
Key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) {
    HashTable *Hc = create_hashtable(candidates,sizeC);
    HashTable *Hv = create_hashtable(voters,sizeV);
    int pos1, pos2;
    while(decl) {
        // On vérifie que la personne qui vote a le droit de voter et qu’elle n’a pas déjà voté
        pos1 = find_position(Hv, decl->data->pKey);
        if((Hv->tab[pos1] != NULL) && (Hv->tab[pos1]->val == 0) ) {
            // On vérifie que la personne sur qui porte le vote est bien un candidat de l’élection
            Key *kCand = str_to_key(decl->data->mess); 
            pos2 = find_position(Hc, kCand);
            if(Hc->tab[pos2]->key != NULL) {
                // Si toutes ces conditions sont vérifiées, le vote est comptabilisé dans la table Hc et la table Hv est mise à jour pour indiquer que ce votant vient de vote
                Hc->tab[pos2]->val++; 
                Hv->tab[pos1]->val++ ; 
            }
            free(kCand);
        } 
        decl = decl->next; 
    }
    // Calculating the winner based on the number of votes
    int score = 0;
    int position;
    Key *keyTmp;
    Key *keyWinner = create_key();

    while(candidates != NULL) {
        // We calculate the position of the candidate in the HashTable
        position = find_position(Hc, candidates->data);

        // If the candidate has more votes than the one currently stored:
        if(((Hc->tab)[position])->val > score) {
            score = ((Hc->tab)[position])->val;
            keyTmp = ((Hc->tab)[position])->key;
            init_key(keyWinner, keyTmp->val, keyTmp->n);
        }
        candidates = candidates->next;
    }
    
    delete_hashtable(Hc);
    delete_hashtable(Hv);
    return keyWinner; 
}