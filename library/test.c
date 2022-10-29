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
#include "include/hashtable.h"
#include "include/infoHashtable.h"
#include "include/array.h"

int main(int argc, char** argv){
    
    THashTable *ht = hashTableCreate(10);

    char key1[6] = "serio";
    char key2[6] = "merda";
    char key3[6] = "pussy";
    char key4[6] = "giggi";

    hashTableInsert(ht, key1, 10);
    hashTableInsert(ht, key2, 20);
    hashTableInsert(ht, key3, 30);
    hashTableInsert(ht, key4, 40);

    hashTablePrint(ht);

    return EXIT_SUCCESS;
}