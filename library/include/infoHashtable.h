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

/**
 * @brief type of HashTable
 * 
 */
typedef int TKey;
typedef float TValue;

/**
 * @brief definition of HashTable
 * 
 */
typedef struct {
    TKey key;
    TValue value;
} TInfo;

/**
 * @brief check if frist value is equal to the second value
 * 
 * @return bool 
 */
bool infoEqual (TInfo, TInfo);

/**
 * @brief check if frist value is greater to the second value
 * 
 * @return bool 
 */
bool infoGreater (TInfo, TInfo);

/**
 * @brief check if frist value is less to the second value
 * 
 * @return bool 
 */
bool infoLess (TInfo, TInfo);

/**
 * @brief structured print of the value
 * 
 */
void infoPrint (TInfo);


unsigned int keyHash (TKey);

#endif