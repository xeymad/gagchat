/**
 * @file test.c
 * @author Gianluca (g.canzolino3@studenti.unisa.it)
 * @brief 
 * @version 0.1
 * @date 2022-10-29
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

#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "infoHashtable.h"
#include "array.h"

typedef struct {
    int v1;
    char* v2;
} prova;

typedef struct {
    int v1;
    TList lista;
} test;

int main(int argc, char** argv){
    THashTable *ht = hashTableCreate();

    char key1[6] = "ciao";
    char key2[6] = "lista";
    char key3[6] = "peppe";
    char key4[6] = "text";
    char key5[6] = "pino";
    char key6[6] = "giuse";
    char key7[6] = "mario";
    char key8[6] = "bohri";
    char key9[6] = "mano";
    char key10[6] = "perra";
    char key11[6] = "barra";
    char key12[6] = "lapto";

    int v = 2;

    prova x;
    x.v1 = 2;
    x.v2 = "peppe";

    test z;

    z.lista=listCreate();

    TInfoList info;
    info.key="ciao";
    info.value=10;

    z.lista=listInsert(z.lista, info);

    TInfoList info2;
    info2.key="peppe";
    info2.value=20;
    z.lista=listInsert(z.lista, info2);

    hashTableInsert(ht, key1, (void *)&x);

    hashTableInsert(ht, key2, (void *)&z);
    hashTableInsert(ht, key3, (void *)&v);
    hashTableInsert(ht, key4, (void *)&v);
    hashTableInsert(ht, key5, (void *)&v);
    hashTableInsert(ht, key6, (void *)&v);
    hashTableInsert(ht, key7, (void *)&v);
    hashTableInsert(ht, key8, (void *)&v);
    hashTableInsert(ht, key9, (void *)&v);
    hashTableInsert(ht, key10, (void *)&v);
    hashTableInsert(ht, key11, (void *)&v);
    hashTableInsert(ht, key12, (void *)&v);

    test *k = (test *)hashTableSearch(ht, key2);

    listPrint(k->lista);

    hashTablePrint(ht);
    
    /*
    printf("\n\n\nCerco:\n");

    printf("%s %d %s\n", ht->bucket[13].key, ((prova *)ht->bucket[13].value)->v1, ((prova *)ht->bucket[13].value)->v2);
        
    x.v1 = 3;
    x.v2 = "giorgio";

    hashTableInsert(ht, key1, (void *)&x);

    printf("%s %d %s\n", ht->bucket[13].key, ((prova *)ht->bucket[13].value)->v1, ((prova *)ht->bucket[13].value)->v2);
     
    prova *y = (prova *)hashTableSearch(ht, key1);
    
    printf("y: v1->%d \t v2->%s\n", y->v1, y->v2);
    


    hashTablePrint(ht);

    hashTableDelete(ht, key1);

    hashTablePrint(ht);

    hashTableDestroy(ht);
    */
    return EXIT_SUCCESS;
}