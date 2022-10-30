/**
 * @file infoList.c
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
#include "infoList.h"

TInfoList infoListCreateKey(TKeyList key) {
    TInfoList info;
    info.key = key;

    return info;
}

TInfoList infoListCreate(TKeyList key, TValueList value) {
    TInfoList info;
    info.key = key;
    info.value = value;

    return info;
}

int infoListEqual(TInfoList info1, TInfoList info2) {
    return info1.key == info2.key;
}

int infoListGreater(TInfoList info1, TInfoList info2) {
    return info1.key > info2.key;
}

int infoListLess(TInfoList info1, TInfoList info2) {
    return info1.key < info2.key;
}

void infoListPrint(TInfoList info) {
    printf("%d\t%d\n", info.key, info.value);
}