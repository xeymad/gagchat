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
#include <string.h>
#include "infoList.h"
#include "list.h"
#include "hashtable.h"
#include "infoHashtable.h"

/*
 * Operazioni su THashTable
 */

/**
 * @brief Creation of a new HashTable
 *
 * @return THashTable*
 */
THashTable *hashTableCreate()
{
    THashTable *ht = malloc(sizeof(THashTable));
    assert(ht != NULL);

    ht->bucket = malloc(CAPACITY * sizeof(TBucket));
    assert(ht->bucket != NULL);

    for (int i = 0; i < CAPACITY; i++)
    {
        ht->bucket[i].value = NULL;
    }

    ht->n_bucket = CAPACITY;
    return ht;
}

/**
 * @brief destroy the HashTable
 *
 * @param ht pointer of HashTable
 */
void hashTableDestroy(THashTable *ht)
{
    free(ht->bucket);
    free(ht);
}

/**
 * @brief search a key in a HashTable, return the list
 *
 * @param ht pointer of HashTable
 * @param key key to find
 * @return TValueHashtable
 */
TValueHashtable hashTableSearch(THashTable *ht, TKeyHashtable key)
{
    u_int64_t h = keyHash(key) % ht->n_bucket;
    u_int64_t dx = keyHashD(key);

    for (int tmp = 0; tmp < ht->n_bucket; tmp++)
    {
        if (ht->bucket[h].value == NULL)
        {
            return NULL;
        }
        else
        {
            if (strcmp(ht->bucket[h].key, key) == 0)
            {
                return ht->bucket[h].value;
            }
        }
        h = (h + dx) % ht->n_bucket;
    }
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
    u_int64_t h = keyHash(key) % ht->n_bucket;
    u_int64_t dx = keyHashD(key);

    for (int tmp = 0; tmp < ht->n_bucket; tmp++)
    {

        if (ht->bucket[h].value == NULL)
        {
            ht->bucket[h].key = key;
            ht->bucket[h].value = value;
            return;
        }
        else
        {
            if (strcmp(ht->bucket[h].key, key) == 0)
            {
                ht->bucket[h].key = key;
                ht->bucket[h].value = value;
                return;
            }
        }
        h = (h + dx) % ht->n_bucket;
    }
}

/**
 * @brief Delete a key in a HashTable
 *
 * @param ht pointer of HashTable
 * @param key key to delete
 */
void hashTableDelete(THashTable *ht, TKeyHashtable key)
{
    u_int64_t h = keyHash(key) % ht->n_bucket;
    u_int64_t dx = keyHashD(key);

    for (int tmp = 0; tmp < ht->n_bucket; tmp++)
    {
        if (ht->bucket[h].value == NULL)
        {
            return;
        }
        else
        {
            if (strcmp(ht->bucket[h].key, key) == 0)
            {
                ht->bucket[h].key = NULL;
                ht->bucket[h].value = NULL;
            }
        }
        h = (h + dx) % ht->n_bucket;
    }
}

/**
 * @brief Print a HashTable
 *
 * @param ht pointer of HashTable
 */
void hashTablePrint(THashTable *ht)
{
    for (int i = 0; i < ht->n_bucket; i++)
    {
        printf("bucket[%d] = key -> %s; value -> %p\n", i, ht->bucket[i].key, ht->bucket[i].value);
     
    }
}