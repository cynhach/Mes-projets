#include "blockTree.h"

void submite_vote(Protected* p) {
	FILE* fichier = fopen("Pending_votes.txt", "a");
	if(!fichier) return;
	fprintf(fichier, "%s\n", protected_to_str(p));
	fclose(fichier);
}

void create_block(CellTree* tree, Key* author, int d) {
	CellProtected* votes = read_protected("Pending_votes.txt");
	CellTree* leaf = last_node(tree);
	Block* b = create_block(author, votes, (unsigned char*)"", leaf->block->hash, 0);
	compute_proof_of_work(b, d);
	assert(remove("Pending_votes.txt") == 0);
	save_block("Pending_block.txt", b);
	free(b->hash);
	free(b->previous_hash);
	delete_list_protected(b->votes);
	free(b);
}

void add_block(int d, char* name) {
	Block* b = read_block("Pending_block.txt");
	if(verify_block(b, d)) {
		strcat(path)
		save_block(path, b);
	}
	assert(remove("Pending_block.txt") == 0);
	free(b->hash);
	free(b->previous_hash);
	delete_list_protected(b->votes);
	free(b);
}

CellTree* read_tree() {

}

Key* compute_winner_BT(CellTree* tree, CellKey* candidates, CellKey* voters, int sizeC, int sizeV) {
	//verification de sizeC >= len(candidates) && sizeV >= len(voters)
    assert(   (sizeC >= listKeyLength(candidates))   &&   (sizeV >= listKeyLength(voters))   );

    //extraction de la liste des declarations de vote valides
    CellProtected * votes = votesBrancheMax(tree);
    thwarted(&votes);

    //Calcul du gagnant
    Key *gagnant = compute_winner(votes, candidates, voters, sizeC, sizeV);
    
    //on libere les cellules mais pas les protected
    CellProtected *tmp;
    while (votes)   {
        tmp = votes;
        votes = votes->next;
        free(tmp);
    }
    return gagnant;
}