/**
 * @file infoList.h
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

#ifndef INFOLIST_H
#define INFOLIST_H

typedef int TKey;
typedef int TValue;

struct SInfoList {
    TKey key;
    TValue value;
};
typedef struct SInfoList TInfoList;

TInfoList infoListCreateKey(TKey key);
TInfoList infoListCreate(TKey, TValue);
int infoListEqual (TInfoList, TInfoList);
int infoListGreater (TInfoList, TInfoList);
int infoListLess (TInfoList, TInfoList);
void infoListPrint (TInfoList);

#endif
