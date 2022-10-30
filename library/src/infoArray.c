/**
 * @file infoArray.c
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

/*
 * TInfoArray: tipo elementare
 */

#include <stdio.h>
#include "infoArray.h"

TInfoArray infoArrayCreate(int value) {
    return value;
}

bool infoArrayEqual(TInfoArray info1, TInfoArray info2) {
    return info1 == info2;
}

bool infoArrayGreater(TInfoArray info1, TInfoArray info2) {
    return info1 > info2;
}

bool infoArrayLess(TInfoArray info1, TInfoArray info2) {
    return info1 < info2;
}

void infoArrayPrint(TInfoArray info) {
    printf("%d\n", info);
}