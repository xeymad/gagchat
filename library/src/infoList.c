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
#include <string.h>
#include "infoList.h"

/**
 * @brief check if all the information of frist value 
 *        are the same of the second value
 * 
 * @return bool 
 */
int infoListEqual(TInfoList info1, TInfoList info2)
{
    if (info1.user != NULL && info1.user != NULL && strcmp(info1.user, info2.user) == 0)
    {
        if (info1.text != NULL && info1.text != NULL && strcmp(info1.text, info2.text) == 0)
        {
            if (info1.code == info2.code)
            {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * @brief structured print of the value
 * 
 */
void infoListPrint(TInfoList info)
{
    printf("User %s\nMessage %s\nCode %d\n\n",
           info.user, info.text, info.code);
}