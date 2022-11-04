/**
 * @file redblackTree.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022 - All Rights Reserved
 * 
 * This file is part of <<ProjectName>>.
 * <<ProjectName>> is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * <<ProjectName>> is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with <<ProjectName>>. If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include "redblackTree.h"
#include <stdlib.h>
#include <assert.h>

RBTree* rbtree_create(int (*comparator)(const void*,const void*)){
	RBTree* tree = malloc(sizeof(RBTree));
    assert(tree!=NULL);
	tree->guard = treenode_createGuard();
	tree->root = tree->guard;
	tree->comparator = comparator;
	return tree;
}

void rbtree_insert(RBTree* rbtree, void* data){
	treenode_insertion(&rbtree->root,data,rbtree->comparator,rbtree->guard);
}

void rbtree_deleteData(RBTree* rbtree, void* data){
	treenode_DeleteData(&rbtree->root,data,rbtree->comparator,rbtree->guard);
}

// void rbtree_print(RBTree* rbtree){
// 	treenode_printTree(stdout,rbtree->root,rbtree->guard);
// }

void rbtree_destroy(RBTree* rbtree){
    treenode_deleteTree(rbtree->root,rbtree->guard);
    free(rbtree);
    rbtree=NULL;
}
