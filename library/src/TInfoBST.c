/**
 * @file TInfoBST.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief tipo elementare TInfoBST
 * @version 0.1
 * @date 2022-11-04
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
#include "TInfoBST.h"
#include <string.h>

int infoBSTEqual (TInfoBST info1, TInfoBST info2) {
    return (strcmp(info1,info2)==0);
}

int infoBSTGreater (TInfoBST info1, TInfoBST info2) {
    return  (strcmp(info1,info2)>0);
}

int infoBSTLess (TInfoBST info1, TInfoBST info2) {
    return  (strcmp(info1,info2)<0);
}

void infoBSTPrint (TInfoBST info) {
    printf ("%s ", info);
}
