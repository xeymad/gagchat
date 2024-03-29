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

#ifndef INFO_LIST_H
#define INFO_LIST_H

#include "message.h"

/**
 * @brief type of List
 * 
 */
typedef Message TInfoList;

/**
 * @brief check if all the information of frist value 
 *        are the same of the second value
 * 
 * @return bool 
 */
int infoListEqual (TInfoList, TInfoList);

/**
 * @brief structured print of the value
 * 
 */
void infoListPrint (TInfoList);

#endif
