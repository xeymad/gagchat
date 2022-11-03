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
#include <string.h>
#include "infoList.h"
#include "list.h"
#include <time.h>

typedef struct {
    int v1;
    int v2;
} prova;

typedef struct {
    int v1;
    TList lista;
} test;


int main(int argc, char** argv){
    TList list = listCreate();

    Message mess, mess2;

    strcpy(mess.user, "Pippo");
    strcpy(mess.text, "Ciao come stai?");
    mess.code = 2;

    strcpy(mess2.user, "Pluto");
    strcpy(mess2.text, "Sto bene");
    mess2.code = 3;

    list = listInsert(list, mess);
    list = listInsert(list, mess2);

    printf("Ciao\n");

    listPrint(list);

    Message mess3;

    strcpy(mess3.user, "Pippo");
    strcpy(mess3.text, "Come va?");
    mess3.code = 2;

    THLNode* n = listSearch(list, mess3);
    if(n != NULL)
    printf("Trovato user %s text %s\n", n->info.user, n->info.text);
    //printf("Valore associato a %s: %d\n",testare, *(int *)hashTableSearch(ht, testare));
}