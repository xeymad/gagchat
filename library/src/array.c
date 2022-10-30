/**
 * @file array.c
 * @author Gianluca (g.canzolino3@studenti.unisa.it)
 * @brief 
 * @version 0.1
 * @date 2022-10-30
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

#include <stdlib.h>
#include <assert.h>
#include "array.h"

#define C_EXP 5  // costante di espansione
#define C_RED 10 // costante di riduzione

TArray arrayCreate(int length) {
    TArray a;
    int size = length + C_EXP;
    a.items = malloc(size * sizeof (TInfoArray));
    assert(a.items != NULL);
    a.length = length;
    a.size = size;
    return a;
}

void arrayDestroy(TArray *a) {
    free(a->items);
    a->items = NULL;
    a->length = a->size = 0;
}

void arrayResize(TArray *a, int length) {
    if (length > a->size || length < a->size - C_RED) {
        int size = length + C_EXP;
        a->items = realloc(a->items, size * sizeof (TInfoArray));
        assert(a->items != NULL);
        a->size = size;
    }
    a->length = length;
}

void arrayPrint(TArray *a) {
    for (int i = 0; i < a->length; ++i) {
        infoArrayPrint(a->items[i]);
    }
}
TArray arrayInsert(TArray *a,TInfoArray item){
    arrayResize(a,a->length-1);
    a->items[a->length-1]=item;
}