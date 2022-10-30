/**
 * @file infoArray.h
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
 * TInfoArray: tipo elementare
 */

#ifndef INFO_ARRAY_H
#define INFO_ARRAY_H

#include "stdbool.h"

/**
 * @brief type of Array
 * 
 */
typedef int TInfoArray;

/**
 * @brief check if frist value is equal to the second value
 * 
 * @return bool 
 */
bool infoArrayEqual(TInfoArray, TInfoArray);

/**
 * @brief check if frist value is greater to the second value
 * 
 * @return bool 
 */
bool infoArrayGreater(TInfoArray, TInfoArray);

/**
 * @brief check if frist value is less to the second value
 * 
 * @return bool 
 */
bool infoArrayLess(TInfoArray, TInfoArray);

/**
 * @brief structured print of the value
 * 
 */
void infoArrayPrint(TInfoArray);

#endif



