/**
 * @file array.h
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
 * TArray: array dinamico
 */

#ifndef TARRAY_H
#define TARRAY_H

#include "infoArray.h"

/**
 * @brief Struct of Array
 * 
 */
typedef struct {
    TInfoArray* items; // puntatore agli elementi dell'array
    int length;   // lunghezza array    
    int size;     // dimensione allocata (>= length)
} TArray;

/**
 * @brief Creation of a new Array
 * 
 * @param length size of Array
 * @return TArray 
 */
TArray arrayCreate (int length);

/**
 * @brief destroy the Array
 * 
 * @param a pointer of Array
 */
void arrayDestroy (TArray *a);

/**
 * @brief resize the Array
 * 
 * @param a pointer of Array
 * @param length size of Array
 */
void arrayResize (TArray *a, int length);

/**
 * @brief 
 * 
 * @param a pointer of Array
 */
void arrayPrint (TArray *a);

/**
 * @brief 
 * 
 * @param a pointer of Array
 * @param item item to insert
 * @return TArray 
 */
TArray arrayInsert(TArray *a,int item);

#endif /* TARRAY_H */

