/**
 * @file treeNode.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief 
 * @version 0.1
 * @date 2022-11-04
 * 
 * @copyright Copyright (c) 2022 - All Rights Reserved
 * 
 * This file is part of gagchat.
 * gagchat is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gagchat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gagchat. If not, see <http://www.gnu.org/licenses/>.
 * 
 */
#include <stdlib.h>
#include "treeNode.h"

void treenode_LeftRotate(Treenode **root,Treenode * x, Treenode * guard){
	Treenode * y = x->right;		
	x->right = y->left;				 
									// left child of y becomes the right child of x
	if(y->left!=guard)
		y->left->parent = x;
								// y becomes the root of the subtree
	y->parent = x->parent;
	
	if(x->parent==guard)		// if x was root now y is the root
		*root = y;
	else if(x==x->parent->left)		// if x was in the left of the parent
		x->parent->left = y;
	else x->parent->right = y;		// if x was in the right of the parent
	y->left = x;				// x becomes the left child of y
	x->parent = y;
}

void treenode_RightRotate(Treenode **root,Treenode * x, Treenode * guard){
 	Treenode * y = x->left;
	x->left = y->right;
		
	if(y->right!=guard)
		y->right->parent = x;

	y->parent = x->parent;
	
	if(x->parent==guard)
		*root = y;
	else if(x==x->parent->right)
		x->parent->right = y;
	else x->parent->left = y;
	y->right = x;
	x->parent = y;
}

void treenode_insertion(Treenode ** root,void* data,int (*comparator)(const void*,const void*), Treenode * guard){
	Treenode * z = malloc(sizeof(Treenode));
	z->data = data;
	z->left = guard;
	z->right = guard;
	z->parent = guard;
	if(*root == guard){
		z->color = 'B';
		*root = z;
		return;
	}
	Treenode * y = guard;
	Treenode * x = *root;
		
	while(x!=guard){			// stop when x finds the last node and save it at y, x becomes guard
		y = x;
		if(comparator(z->data, x->data)<0)
			x = x->left;
		else x = x->right;
	}
	z->parent = y;
	
	if(comparator(z->data, y->data)<0) //put z right or left,depends on the id
		y->left = z;
	else 
		y->right = z;

	z->color = 'R';
	treenode_Fixedinsertion(root,z,guard);
}

void treenode_Fixedinsertion(Treenode **root,Treenode * z, Treenode * guard){	// we insert z in this function with color red
	Treenode * y;
	while(z->parent->color == 'R'){		// if both child and parent are red
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;		// y is the uncle
			if(y->color == 'R'){			// if uncle is red, then all three are red
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}else{							// if uncle is black
				if(z == z->parent->right){	// if we have a triangle form
					z = z->parent;
					treenode_LeftRotate(root,z,guard);		// we make it a line
				}
				z->parent->color = 'B';		//we fix the colors in the line, z is the left last node of the subtree
				z->parent->parent->color = 'R';
				treenode_RightRotate(root,z->parent->parent,guard);
			}
		}else if(z->parent == z->parent->parent->right){	// same thing in the right side 
			y = z->parent->parent->left;
			if(y->color == 'R'){
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}else{
				if(z == z->parent->left){
					z = z->parent;
					treenode_RightRotate(root,z,guard);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				treenode_LeftRotate(root,z->parent->parent,guard);
			}
		}
	}
	(*root)->color = 'B'; //root has to be always black
}

Treenode* treenode_FindData(Treenode *root,void* data,int (*comparator)(const void*,const void*), Treenode * guard){	// search tree
	Treenode *temp  = root;																// to find the data

	if(temp==guard || !comparator(temp->data,data))
		return temp;
	if(comparator(temp->data,data)>0){
		temp = temp->left;
		treenode_FindData(temp,data,comparator,guard);
	}
	else if(comparator(temp->data,data)<0){
		temp = temp->right;
		treenode_FindData(temp,data,comparator,guard);
	}
}

void treenode_DeleteData(Treenode **root,void* data,int (*comparator)(const void*,const void*), Treenode * guard){
	Treenode * z = treenode_FindData(*root,data,comparator,guard);
	Treenode * y = z;
	Treenode * x;
	if(z==guard)	//if data doesn't exist return
		return;
	//free(data) 		//delete the node
	char fcolor = y->color;
	if(z->left == guard){		// if z has one child(on the right)
		x = z->right;
		treenode_transplant(root,z,z->right,guard);	// the right child takes place of z
	}else if(z->right == guard){	// if z has one child(on the left)
		x = z->left;
		treenode_transplant(root,z,z->left,guard);		// the left child takes place of z
	}else{								// z has 2 children 
		while (y->right != guard)	// y will be the max of the smaller ids of z
	 	 	y = y->right;
	 	fcolor = y->color;			// save the color before any change 
	 	x = y->right;
	 	if(y->parent == z)	// if z is one node from the end
	 		x->parent = y;	// x->parent was guard, now is y
	 	else{
	 		treenode_transplant(root,y,y->right,guard);	// fix the subtree in the right of z with y as root
	 		y->right = z->right;
	 		y->right->parent = y;
		}
		treenode_transplant(root,z,y,guard); // y takes place of z, coonect the subtree with the left side
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	free(z);	// delete z
	if(fcolor == 'B')
		treenode_FixedDelete(root,x,guard);
}

void treenode_transplant(Treenode **root,Treenode * x,Treenode* y, Treenode * guard){
	if(x->parent == guard)
		*root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->parent = x->parent; 
}

void treenode_FixedDelete(Treenode **root,Treenode * x, Treenode * guard){
	Treenode *w;
	while(x != *root && x->color == 'B'){
		if(x == x->parent->left){
			w = x->parent->right;	// w is the sibling
			if(w->color == 'R'){	// if sibling is red, his children have to be black
				w->color = 'B';		// we reverse the colors of w and x->parent
				x->parent->color = 'R';
				treenode_LeftRotate(root,x->parent,guard);
				w = x->parent->right;	// now sibling of x is one of his sibling's child
			}
			if(w->left->color == 'B' && w->right->color == 'B'){	// his sibling and both sibling's children are black
				w->color = 'R'; // then sibling is red
				x = x->parent;
			}else{
				if(w->right->color == 'B'){  // sibling is black, his left child is red and the right is black
					w->left->color = 'B';	// reverse the colors of w and w->left child
					w->color = 'R';
					treenode_RightRotate(root,w,guard);	
					w = x->parent->right;	// now the sibling is the black node with a red right child
				}
				w->color = x->parent->color;	// fix the colors
				x->parent->color = 'B';
				w->right->color = 'B';
				treenode_LeftRotate(root,x->parent,guard);
				x = *root;
			}

		}
		else{							// same thing on the right side
			w = x->parent->left;
			if(w->color == 'R'){
				w->color = 'B';
				x->parent->color = 'R';
				treenode_RightRotate(root,x->parent,guard);
				w = x->parent->left;
			}
			if(w->right->color == 'B' && w->left->color == 'B'){
				w->color = 'R';
				x = x->parent;
			}else if(w->left->color == 'B'){
				w->right->color = 'B';
				w->color = 'R';
				treenode_LeftRotate(root,w,guard);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = 'B';
			w->left->color = 'B';
			treenode_RightRotate(root,x->parent,guard);
			x = *root;
		}
	}
	x->color = 'B';
}

void treenode_deleteTree(Treenode * root, Treenode * guard){
	if(root==guard)
		return;
	treenode_deleteTree(root->left,guard);
	treenode_deleteTree(root->right,guard);
	//free(root->data);
	free(root);	
}

void treenode_printTree(FILE * f,Treenode * root, Treenode * guard){	//print tree 
	if(root==guard)
		return;
	treenode_printTree(f,root->left,guard);
	printf("%p\n",root->data);
	treenode_printTree(f,root->right,guard);	
}

Treenode* treenode_createGuard(){
	Treenode * guard = malloc(sizeof(Treenode));
	guard->left = guard;
	guard->right = guard;
	guard->parent = guard;
	guard->data = NULL;
	guard->color = 'B';
	return guard;
}