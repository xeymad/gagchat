/**
 * @file hashtable.h
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

#ifndef HASHTABLE_H
#define HASHTABLE_H

//Fowle-Noll-Vo hash function
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define FNV_PRIME_2 10995116282UL
#define CAPACITY 64
#define MAX_LOAD 0.75
#define GROW_FACTOR 2
#define MAX_KEY_SIZE 64

#include "infoHashtable.h"
#include "infoList.h"
#include "list.h"

/**
 * @brief Struct of Hashtable
 * 
 */
typedef struct SBucket
{
    TKeyHashtable key;
    TValueHashtable value;
} TBucket;

typedef struct SHashTable
{
    TBucket *bucket;
    int *used;
    int n_bucket;
    int n_used;
} THashTable;

/**
 * @brief Creation of a new HashTable
 * 
 * @return THashTable* 
 */
THashTable *hashTableCreate();

/**
 * @brief Resize hashtable
 * 
 * @param ht pointer of HashTable
 * @param n new size
 */
void hashTableResize(THashTable *ht, int n);

/**
 * @brief destroy the HashTable
 * 
 * @param ht pointer of HashTable
 */
void hashTableDestroy (THashTable* ht);

/**
 * @brief search in a HashTable
 * 
 * @param ht pointer of HashTable
 * @param key key to find
 * @return TValueHashtable 
 */
TValueHashtable hashTableSearch (THashTable* ht, TKeyHashtable key);

/**
 * @brief Insert a new key and value in a HashTable
 * 
 * @param ht pointer of HashTable
 * @param key key to insert
 * @param value value to insert
 */
void hashTableInsert (THashTable* ht, TKeyHashtable key, TValueHashtable value);

/**
 * @brief Delete a key in a HashTable
 * 
 * @param ht pointer of HashTable
 * @param key key to delete
 */
void hashTableDelete (THashTable* ht, TKeyHashtable key);

/**
 * @brief Print a HashTable
 * 
 * @param ht pointer of HashTable
 */
void hashTablePrint(THashTable* ht);


/**
 * @brief hash a key (function h(x))
 * 
 * @return u_int64_t 
 */
u_int64_t keyHash (TKeyHashtable);

/**
 * @brief hash a key (function d(x))
 * 
 * @return u_int64_t 
 */
u_int64_t keyHashD (TKeyHashtable);

/**
 * @brief double hashing return hash = h(x) + j*d(x)
 * 
 * @return u_int64_t 
 */
u_int64_t keyHashExpande (TKeyHashtable, u_int64_t, int);


#endif 
