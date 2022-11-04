/**
 * @file TBST.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Implementazione TBST.
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
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "TInfoBST.h"
#include "TBST.h"

/* Operazioni sui nodi */

/* Creazione di un nodo 
 * BinarySearchTree (DI TIPO PUNTATORE):
 * Alloco sizeof TBSTnode e inserisco info.
 * I puntatori li lascio a NULL.
*/
TBSTnode *BSTnodeCreate (TInfoBST info) {
    TBSTnode *node = malloc (sizeof(TBSTnode));
    assert (node != NULL);
    node->info = info;
    node->left = node->right = NULL;
    return node;
}

/* Per distruggere un nodo basta deallocarlo
 */
void BSTnodeDestroy (TBSTnode* node) {
    free (node);
}

/* Operazioni sugli alberi - versione ricorsiva */

/*Ritorna un TBST nullo.*/
TBST BSTcreate () {
    return NULL;
}
/*CASO BASE: TBST NULL RETURN NULL
 * DIVIDE: SOTTOALBERI SINISTRO E DESTRO
 * IMPERA: SO CANCELLARE I SOTTOALBERI DESTRO E SINISTRO
 * COMBINA: CANCELLO IL NODO PADRE
 * la funzione ritorna un albero nullo
 * � importante ricordare che TBST serve solo a ritornare un albero nullo
 * e non serve nella ricorsione.
 * la complessit� � 0(n)
 */
TBST BSTdestroy (TBST tree) {
    if (tree == NULL)
        return NULL;
    BSTdestroy(tree->left);
    BSTdestroy(tree->right);
    BSTnodeDestroy (tree);
    return NULL;
}
/* 
 */
TBST BSTsearch (TBST tree, TInfoBST info) {
    if (tree == NULL || infoBSTEqual(info, tree->info))
        return tree;
    if (infoBSTGreater(info, tree->info)) 
        return BSTsearch(tree->right, info);
    else 
        return BSTsearch(tree->left, info);
    return tree;
}

TBST BSTmin (TBST tree) {
    if (tree == NULL || tree->left == NULL)
        return tree;
    return BSTmin (tree->left);
}

TBST BSTmax (TBST tree) {
    if (tree == NULL || tree->right == NULL)
        return tree;
    return BSTmax (tree->right);
}
/*Algoritmo ottimale ricorsivo per inserimento in BST
 * CASO BASE: da completare
 */
TBST BSTinsert (TBST tree, TInfoBST info) {
    if (tree == NULL)
        return BSTnodeCreate(info);
    if (infoBSTGreater(info, tree->info)) 
        tree->right = BSTinsert(tree->right, info);
    else 
        tree->left = BSTinsert(tree->left, info);
    return tree;
}
/*FUNZIONE PIU' DIFFICILE
 * 3 CASI: 
 * Devo cancellare un elemento che NON ha un sottoalbero sinistro.
 * Il TBST mantiene la sua propriet� se cancello il nodo e sostituisco 
 * al puntatore a destra del nodo precedente il puntatore a destra del nodo cancellato.
 * Questo ragionamento vale anche per le foglie.
 * Vale il viceversa per l'albero destro.
 * L'ultimo caso � quello in cui il nodo da cancellare ha entrambi i sottoalberi.
 * In questo caso, viene preso il minimo DEL SOTTOALBERO DESTRO.
 * BISOGNA TENERE CONTO CHE ABBIAMO GIA' BSTmin. 
 */
TBST BSTdelete (TBST tree, TInfoBST info) {
    if (tree == NULL)
        return NULL;
    if (infoBSTGreater(info, tree->info)) 
        tree->right = BSTdelete(tree->right, info);
    else if (infoBSTLess(info, tree->info))
        tree->left = BSTdelete(tree->left, info);
    else { // trovato il nodo da rimuovere
        if (tree->left == NULL) {
            TBST right = tree->right;
            BSTnodeDestroy(tree);
            tree = right;
        } else if (tree->right == NULL) {
            TBST left = tree->left;
            BSTnodeDestroy(tree);
            tree = left;
        } else {
            TBST min = BSTmin(tree->right);
            tree->info = min->info;
            tree->right = BSTdelete(tree->right, min->info);
        }
    }
    return tree;
}
/* VISITA IN ORDER
 * per gli altri due tipi di visite basta semplicemente
 * scambiare infoBSTPrint.
 */
void BSTprint (TBST tree) {
    if (tree != NULL) {
        BSTprint(tree->left);
        infoBSTPrint(tree->info);
        BSTprint(tree->right);
    }
}

/* versione iretativa di alcuni algoritmi */

TBST BSTsearchI (TBST tree, TInfoBST info) {
    
    while (tree != NULL && !infoBSTEqual(tree->info, info)) {
        if (infoBSTGreater (info,  tree->info))
            tree = tree->right;
        else
            tree = tree->left;
    }
    return tree;
}

TBST BSTinsertI (TBST tree, TInfoBST info) {
    
    TBSTnode *node = tree;
    TBSTnode *prec = NULL;     
    TBSTnode *new = BSTnodeCreate(info);
    int right;

    /* cerca il punto d'inserimento */
    while (node != NULL) {
        prec = node;
        right = infoBSTGreater (info,  node->info);
        if (right)
            node = node->right;
        else
            node = node->left;
    }     

    /* inserisce il nuovo nodo */
    if(prec == NULL)
        return new;
    if (right) 
        prec->right = new;
    else
        prec->left = new;
    return tree;
}
 
TBST BSTdeleteI (TBST tree, TInfoBST info) {
    
    TBSTnode *node = tree;
    TBSTnode *prec = NULL;     
    int right;

    /* cerca il nodo da cancellare */  
    while (node != NULL && !infoBSTEqual(node->info, info)) {
        prec = node;
        right = infoBSTGreater (info,  node->info);
        if (right)
            node = node->right;
        else
            node = node->left;
    }     

    /* nodo non trovato */  
    if (node == NULL)
        return tree;

    /* nodo foglia o con un solo figlio */  
    if (node->left == NULL || node->right == NULL) {
        TBSTnode *succ; // nodo da agganciare     
        if (node->right == NULL)
            succ = node->left;
        else
            succ = node->right;
        BSTnodeDestroy(node);
        if (prec == NULL) // è stata cancellata la radice
            return succ;
        else if (right)
            prec->right = succ;
        else
            prec->left = succ;
        return tree;
    }

    /* nodo con entrambi i figli */  
    TBSTnode* min = BSTmin(node->right);
    node->info = min->info; // sostituisce info con il minimo a destra
    prec = node;
    node = node->right;
    right = 1;
    while (node->left != NULL) { // si posiziona sul nodo con il minimo
        prec = node;
        node = node->left;
        right = 0;
    }
    if (right) // lo esclude
        prec->right = node->right;
    else
        prec->left = node->right;
    BSTnodeDestroy(node); // lo rimuove
    return tree;
}

/* funzioni utili a visualizzare la struttura di un albero binario di interi 
 * (valgono solo per TInfoBST = int)
 */

int BSTdepth(TBST tree){
    if(tree == NULL)
        return -1;
    int hl = BSTdepth(tree->left);
    int hr = BSTdepth(tree->right);
    return (hl > hr)?(hl + 1):(hr + 1);
}

void BSTprintStructure1(TBST tree, int o, TInfoBST* n, int* m) {
    if (tree != NULL) {
        n[o] = tree->info;
        m[o] = 1;
        BSTprintStructure1(tree->left, (o+1)*2-1, n, m);
        BSTprintStructure1(tree->right, (o+1)*2, n, m);
    }
}

// void BSTprintStructure(TBST tree) {
//     int d = BSTdepth(tree)+1, s = pow(2,d)-1, m[s], i, j, b;
//     TInfoBST n[s];
//     for (i = 0; i < s; ++i) // annulla elementi
//         m[i] = 0;
//     BSTprintStructure1(tree, 0, n, m);
//     for (i = 0; i < d; ++i) { // stampa albero
//         for (j = pow(2,i)-1; j < pow(2,i+1)-1; ++j) {
//             b = (pow(2,(d-i-1))-1)*4;
//             if (m[j])
//                 printf("%*d%*s", b/2+4, n[j], b/2, "");
//             else
//                 printf("%*s", b+4,  "");
//         }
//         printf("\n");
//     }
// }