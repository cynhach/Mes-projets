#ifndef TREE_H
#define TREE_H

#include "block.h"

typedef struct block_tree_cell {
	Block* block;
	struct block_tree_cell* father;
	struct block_tree_cell* firstChild;
	struct block_tree_cell* nextBro;
	int height;
} CellTree;

CellTree* create_node(Block* b);
int update_height(CellTree* father, CellTree* child);
void add_child(CellTree* father, CellTree* child);
void print_tree(CellTree* tree);
void delete_node(CellTree* node);
void delete_tree(CellTree* tree);
CellTree* highest_child(CellTree* cell);
CellTree* last_node(CellTree* tree);

#endif