/**
 * @file redblackTree.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief RedBlack tree implementation.
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
#include "treeNode.h"

typedef struct{
	Treenode *root;
	Treenode *guard;
	int (*comparator)(const void*,const void*);
}RBTree;

RBTree* rbtree_create(int (*comparator)(const void*,const void*));

void rbtree_insert(RBTree* rbtree, void* data);

void rbtree_deleteData(RBTree* rbtree, void* data);

// void rbtree_print(RBTree* rbtree);

void rbtree_destroy(RBTree* rbtree);