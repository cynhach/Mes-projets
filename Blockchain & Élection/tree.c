#include "tree.h"
#include <math.h>

CellTree* create_node(Block* b) {
	if(b == NULL) {
		fprintf(stderr, "%s; %s; l.%d: Block Allocation ERROR\n", __FILE__, __PRETTY_FUNCTION__, __LINE__);
    	exit(EXIT_FAILURE);
	} 
	CellTree* tree = (CellTree*) malloc(sizeof(CellTree));
	tree->block = b;
	tree->father = NULL;
	tree->firstChild = NULL;
	tree->nextBro = NULL;
	tree->height = 0;

	return tree;
}

int update_height(CellTree* father, CellTree* child) {
	int max = fmax(father->height, child->height+1);
	if(max == father->height) {
		return 0;
	}
	father->height = max;
	return 1;
}

void add_child(CellTree* father, CellTree* child) {
	if(!father) return;
	// Ajout en tete du fils
	child->nextBro = father->firstChild;
	father->firstChild = child;
	// On modifie la hauteur
	CellTree* ftmp = father;
	CellTree* ctmp = father->firstChild;
	while(ftmp) {
		update_height(ftmp, ctmp);
		ftmp = ftmp->father;
		ctmp = ctmp->father;
	}
}

void print_tree(CellTree* tree) {
	if(!tree)
		return;
	printf("Block de hauteur %d posséde l'ID %s\n", tree->height, tree->block->hash);
	if(tree->nextBro)
		print_tree(tree->nextBro);
	if(tree->firstChild)
		print_tree(tree->firstChild);
}

void delete_node(CellTree* node) {
	delete_block(node->block);
	free(node);
}

void delete_tree(CellTree* tree) {
	if (tree != NULL) {
    	// Deleting the brothers and the sons, and finally the node
    	delete_tree(tree->firstChild);
    	delete_tree(tree->nextBro);
    	// Deleting the node when deprived of any bond
    	delete_node(tree);
    }
}

CellTree* highest_child(CellTree* cell) {
	if(!(cell->firstChild)) return NULL;
	CellTree* child = cell->firstChild->nextBro;
	CellTree* max = cell->firstChild;
	while(child) {
		if(max->height < child->height) {
			max = child;
		}
		child = child->nextBro;
	}
	return max;
}

CellTree* last_node(CellTree* tree) {
	if(!(tree->firstChild)) return tree;
	return last_node(highest_child(tree));
}