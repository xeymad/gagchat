/**
 * @file treeNode.h
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
#include <stdio.h>

typedef struct Treenode{
    void* data;
    char color;
    struct Treenode* left;
    struct Treenode* right;
    struct Treenode* parent;
}Treenode;

Treenode* treenode_createGuard();

void treenode_LeftRotate(Treenode **root,Treenode* x, Treenode * guard);

void treenode_RightRotate(Treenode **root,Treenode* y, Treenode * guard);

void treenode_insertion(Treenode **root,void* data,int (*comparator)(const void*,const void*), Treenode * guard);

void treenode_Fixedinsertion(Treenode **root,Treenode* z, Treenode * guard);

void treenode_deleteTree(Treenode * root, Treenode * guard);

Treenode* treenode_FindData(Treenode *root,void* data,int (*comparator)(const void*,const void*), Treenode * guard);

void treenode_DeleteData(Treenode **root,void* data,int (*comparator)(const void*,const void*), Treenode * guard);

void treenode_FixedDelete(Treenode **root,Treenode* x, Treenode * guard);

void treenode_transplant(Treenode **root,Treenode * x,Treenode* y, Treenode * guard);

// void treenode_printTree(FILE * f,Treenode * root, Treenode * guard);