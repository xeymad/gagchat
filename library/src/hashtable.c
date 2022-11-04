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
    ht->used = malloc(CAPACITY * sizeof(int));
    assert(ht->bucket != NULL && ht->used != NULL);

    for (int i = 0; i < CAPACITY; i++)
    {
        ht->bucket[i].value = NULL;
        ht->used[i] = 0;
    }

    ht->n_bucket = CAPACITY;
    ht->n_used = 0;

    return ht;
}

/**
 * @brief resizing Hashtable
 * 
 * @param ht pointer of HashTable
 * @param n new size
 */
void hashTableResize(THashTable *ht, int n)
{
    TBucket *bucket = ht->bucket;
    int *used = ht->used;
    int n_bucket = ht->n_bucket;

    ht->bucket = malloc(n * sizeof(TBucket));
    ht->used = malloc(n * sizeof(int));
    assert(ht->bucket != NULL && ht->used != NULL);

    ht->n_bucket = n;
    ht->n_used = 0;

    for (int i = 0; i < n; i++)
    {
        ht->used[i] = 0;
    }

    for (int i = 0; i < n_bucket; i++)
    {
        if (used[i] && bucket[i].key != NULL)
        {
            hashTableInsert(ht, bucket[i].key, bucket[i].value);
        }
    }

    free(bucket);
    free(used);
}

/**
 * @brief destroy the HashTable
 *
 * @param ht pointer of HashTable
 */
void hashTableDestroy(THashTable *ht)
{
    free(ht->bucket);
    free(ht->used);
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
        if (!ht->used[h])
        {
            return NULL;
        }
        else
        {
            if (ht->bucket[h].key != NULL)
            {
                if (strcmp(ht->bucket[h].key, key) == 0)
                {
                    return ht->bucket[h].value;
                }
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
    if (ht->n_used >= ht->n_bucket * MAX_LOAD)
    {
        hashTableResize(ht, ht->n_bucket * GROW_FACTOR + 1);
    }

    u_int64_t h = keyHash(key) % ht->n_bucket;
    u_int64_t dx = keyHashD(key);

    for (int tmp = 0; tmp < ht->n_bucket; tmp++)
    {

        if (ht->bucket[h].key == NULL)
        {
            ht->bucket[h].key = malloc(strlen(key) * sizeof(ht->bucket[h]));
            strcpy(ht->bucket[h].key, key);
            ht->bucket[h].value = value;
            ht->used[h] = 1;
            ht->n_used++;
            return;
        }
        else
        {
            if (strcmp(ht->bucket[h].key, key) == 0)
            {
                ht->bucket[h].key = malloc(strlen(key) * sizeof(ht->bucket[h]));
                strcpy(ht->bucket[h].key, key);
                ht->bucket[h].value = value;
                ht->used[h] = 1;
                ht->n_used++;
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
        if (!ht->used[h])
        {
            return;
        }
        else
        {
            if (ht->bucket[h].key!=NULL && strcmp(ht->bucket[h].key, key) == 0)
            {
                free(ht->bucket[h].key);
                ht->bucket[h].key = NULL;
                ht->bucket[h].value = NULL;
                ht->n_used--;
                return;
                // ht->used[h] = 0;
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
        printf("bucket[%d] = key -> %s; value -> %p; used -> %d\n", i, ht->bucket[i].key, ht->bucket[i].value, ht->used[i]);
    }
}

/**
 * @brief hash a key (function h(x))
 * 
 * @return u_int64_t 
 */
u_int64_t keyHash(TKeyHashtable key)
{
    u_int64_t hash = FNV_OFFSET;

    // h(x)
    for (const char *p = key; *p; p++)
    {
        hash ^= (u_int64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }

    return hash;
}

/**
 * @brief hash a key (function d(x))
 * 
 * @return u_int64_t 
 */
u_int64_t keyHashD(TKeyHashtable key)
{
    u_int64_t hash2 = FNV_OFFSET;

    // d(x)
    for (const char *p = key; *p; p++)
    {
        hash2 ^= (u_int64_t)(unsigned char)(*p);
        hash2 *= FNV_PRIME_2;
    }

    // printf("key: %s -- h(x): %lu - d(x) = %lu\n", key, hash, hash2);
    return hash2;
}

/**
 * @brief double hashing return hash = h(x) + j*d(x)
 * 
 * @return u_int64_t 
 */
u_int64_t keyHashExpande(TKeyHashtable key, u_int64_t hash, int j)
{
    u_int64_t hash2 = FNV_OFFSET;

    // d(x)
    for (const char *p = key; *p; p++)
    {
        hash2 ^= (u_int64_t)(unsigned char)(*p);
        hash2 *= FNV_PRIME_2;
    }

    // printf("key: %s -- h(x): %lu - d(x) = %lu\n", key, hash, hash2);
    return hash + j * hash2;
}
