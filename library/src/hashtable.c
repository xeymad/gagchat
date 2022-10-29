/**
 * @file hashtable.c
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
#include <stdbool.h>
#include <assert.h>
#include "../include/infoList.h"
#include "../include/list.h"
#include "../include/hashtable.h"

unsigned int keyHash(TKeyHashtable key)
{
    return (unsigned int)key;
}

/* 
 * Operazioni su THashTable
 */

/**
 * @brief Creation of a new HashTable
 * 
 * @param n number of hashtable bucket
 * @return THashTable* 
 */
THashTable *hashTableCreate(int n)
{
    THashTable *ht = malloc(sizeof(THashTable));
    assert(ht != NULL);

    ht->bucket = malloc(n * sizeof(TList));
    assert(ht->bucket != NULL);

    for (int i = 0; i < n; i++)
        ht->bucket[i] = listCreate();
    ht->n_bucket = n;
    return ht;
}

/**
 * @brief destroy the HashTable
 * 
 * @param ht pointer of HashTable
 */
void hashTableDestroy(THashTable *ht)
{
    for (int i = 0; i < ht->n_bucket; i++)
        ht->bucket[i] = listDestroy(ht->bucket[i]);
    free(ht->bucket);
    free(ht);
}

/**
 * @brief search in a HashTable
 * 
 * @param ht pointer of HashTable
 * @param key key to find
 * @return TValue* 
 */
TValueHashtable *hashTableSearch(THashTable *ht, TKeyHashtable key)
{
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfoList info = infoListCreateKey(key);
    THLNode *node = listSearch(ht->bucket[h], info);
    if (node != NULL)
        return &node->info.value;
    return NULL;
}

/**
 * @brief Insert a new key and value in a HashTable
 * 
 * @param ht pointer of HashTable
 * @param key key to insert
 * @param value value to insert
 */
void hashTableInsert(THashTable *ht, TKeyHashtable key, TValueHashtable value)
{
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfoList info = infoListCreateKey(key);
    info.value = value;
    THLNode *node = listSearch(ht->bucket[h], info);
    if (node != NULL)
        node->info.value = value;
    else
        ht->bucket[h] = listInsert(ht->bucket[h], info);
}

/**
 * @brief Delete a key in a HashTable
 * 
 * @param ht pointer of HashTable
 * @param key key to delete
 */
void hashTableDelete(THashTable *ht, TKeyHashtable key)
{
    unsigned h = keyHash(key) % ht->n_bucket;
    TInfoList t = infoListCreateKey(key);
    listDelete(ht->bucket[h], t);
}

/**
 * @brief Print a HashTable
 * 
 * @param ht pointer of HashTable
 */
void hashTablePrint(THashTable *ht)
{
    for (int i = 0; i < ht->n_bucket; i++)
        for (THLNode *node = ht->bucket[i]; node != NULL; node = node->link)
            infoListPrint(node->info);
}