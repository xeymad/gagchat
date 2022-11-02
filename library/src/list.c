/**
 * @file list.c
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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

/* 
 * Operazioni su THLNode e TList
 */

THLNode *nodeCreate(TInfoList info)
{
    THLNode *new = malloc(sizeof(THLNode));
    if (new != NULL)
    {
        new->info = info;
        new->link = NULL;
    }
    return new;
}

void nodeDestroy(THLNode *node)
{
    free(node);
}

TList listCreate()
{
    return NULL;
}

TList listDestroy(TList list)
{
    THLNode *node;
    while (list != NULL)
    {
        node = list;
        list = list->link;
        nodeDestroy(node);
    }
    return list;
}

TList listInsert(TList l, TInfoList info)
{
    if (l == NULL || infoListGreater(l->info, info))
    {
        THLNode *node = nodeCreate(info);
        assert(node != NULL);
        node->link = l;
        return node;
    }
    TList m = listInsert(l->link, info);
    l->link = m;
    return l;
}

THLNode *listSearch(TList list, TInfoList info)
{
    THLNode *node = list;

    while (node != NULL && !infoListEqual(info, node->info))
        node = node->link;
    return node;
}

TList listDelete(TList list, TInfoList info)
{
    THLNode *prec = NULL, *node = list;
    while (node != NULL && !infoListEqual(info, node->info))
    {
        prec = node;
        node = node->link;
    }
    if (node != NULL && infoListEqual(info, node->info))
    {
        if (prec == NULL)
            list = node->link;
        else
            prec->link = node->link;
        nodeDestroy(node);
    }
    return list;
}

void listPrint(TList list)
{
    THLNode *node = list;
    while (node != NULL)
    {
        infoListPrint(node->info);
        node = node->link;
    }
}