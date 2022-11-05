/**
 * @file TBST.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief 
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
#ifndef TBST_H
#define TBST_H

#include "TInfoBST.h"

struct SBSTnode {
    TInfoBST info;
    struct SBSTnode *left;
    struct SBSTnode *right;
};

typedef struct SBSTnode TBSTnode;
typedef TBSTnode *TBST;

TBSTnode *BSTnodeCreate(TInfoBST);
void BSTnodeDestroy(TBSTnode*);
TBST BSTcreate ();
TBST BSTdestroy (TBST);
TBST BSTsearch (TBST, TInfoBST);
TBST BSTmin (TBST);
TBST BSTmax (TBST);
TBST BSTinsert (TBST, TInfoBST);
TBST BSTdelete (TBST, TInfoBST);
TBST BSTsearchI (TBST, TInfoBST);
TBST BSTinsertI (TBST, TInfoBST);
TBST BSTdeleteI (TBST, TInfoBST);
void BSTprint(TBST);
void BSTprintStructure(TBST);

#endif 

