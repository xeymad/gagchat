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

#include "infoHashtable.h"
#include "infoList.h"
#include "list.h"

typedef struct SHashTable
{
    TList *bucket;
    int n_bucket;
} THashTable;

THashTable *hashTableCreate (int n);
void hashTableDestroy (THashTable* ht);
TValue *hashTableSearch (THashTable* ht, TKey key);
void hashTableInsert (THashTable* ht, TKey key, TValue value);
void hashTableDelete (THashTable* ht, TKey key);
void hashTablePrint(THashTable* ht);

#endif 
