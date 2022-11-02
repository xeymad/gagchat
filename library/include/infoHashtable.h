/**
 * @file infoHashtable.h
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

/*
 * definition of comparator for hashtable
 */

#ifndef INFO_HASHTABLE_H
#define INFO_HASHTABLE_H

#include "stdbool.h"

//Fowle-Noll-Vo hash function
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define FNV_PRIME_2 10995116282UL
#define CAPACITY 17 // for test to change //2048

/**
 * @brief type of HashTable
 * 
 */
typedef char* TKeyHashtable;
typedef void* TValueHashtable;

/**
 * @brief definition of HashTable
 * 
 */
typedef struct {
    TKeyHashtable key;
    TValueHashtable value;
} TInfoHashtable;

/**
 * @brief check if frist value is equal to the second value
 * 
 * @return bool 
 */
bool infoEqual (TInfoHashtable, TInfoHashtable);

/**
 * @brief check if frist value is greater to the second value
 * 
 * @return bool 
 */
bool infoGreater (TInfoHashtable, TInfoHashtable);

/**
 * @brief check if frist value is less to the second value
 * 
 * @return bool 
 */
bool infoLess (TInfoHashtable, TInfoHashtable);

/**
 * @brief structured print of the value
 * 
 */
void infoPrint (TInfoHashtable);

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