/**
 * @file list.h
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

#ifndef LIST_H
#define LIST_H

#include "infoList.h"
#include "array.h"

/**
 * @brief Struct of List
 * 
 */
typedef struct SHLNode THLNode;
struct SHLNode {
    TInfoList info;
    THLNode *link;
};
typedef THLNode* TList;

/**
 * @brief Creation of a new List
 * 
 * @return TList 
 */
TList listCreate();

/**
 * @brief 
 * 
 * @param list pointer of List
 * @return TList 
 */
TList listDestroy(TList list);

/**
 * @brief 
 * 
 * @param list pointer of List
 * @param info value of List
 * @return TList 
 */
TList listInsert(TList list, TInfoList info);

/**
 * @brief 
 * 
 * @param list pointer of List
 * @param info value of List
 * @return THLNode* 
 */
THLNode *listSearch(TList list, TInfoList info);

/**
 * @brief 
 * 
 * @param list pointer of List
 * @param info value of List
 * @return TList 
 */
TList listDelete(TList list, TInfoList info);

/**
 * @brief 
 * 
 * @param list pointer of List
 */
void listPrint(TList list);

#endif