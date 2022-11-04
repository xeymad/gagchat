/**
 * @file test.c
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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//#include "message.h"
#include "gui.h"
#include "queue.h"

int main(int argc, char** argv){
    Message msg;
    strcpy(msg.user, "User1");
    strcpy(msg.text, "Ciao come stai?");
    msg.code = 1;

    TQueue* q = queueCreate(10);

    queueAdd(q, msg);

    strcpy(msg.user, "User2");
    strcpy(msg.text, "Merdaccia che sei, lotaaaaa merdaaaa lotaaaa schiet giggi merda");
    msg.code = 1;

    queueAdd(q, msg);

    strcpy(msg.user, "User1");
    strcpy(msg.text, "Ohhhh chin e corn");
    msg.code = 1;

    queueAdd(q, msg);


    printf("\n\n\n");

    strcpy(msg.user, "User2");
    strcpy(msg.text, "Cocco bello, sei un pisello, non bello ma simpatichello. Scherzo sei una lota");
    msg.code = 1;
    for(int i=0; i<8; i++){
        queueAdd(q, msg);
    }

    //queuePrint(q);
    
    gui_print(queueRemove(q), true);
    gui_print(queueRemove(q), false);
    gui_print(queueRemove(q), true);
    gui_print(queueRemove(q), false);
    gui_print(queueRemove(q), true);
    gui_print(queueRemove(q), true);
    gui_print(queueRemove(q), false);
    gui_print(queueRemove(q), true);


}


/*
int main(int argc, char** argv){
    
    Message msg;
    strcpy(msg.user, "User1");
    strcpy(msg.text, "Ciao come stai? sdjsdjsad ashjahd jash shdbasnd hasd hagsd");
    msg.code = 1;

    gui_print(msg, true);

    Message msg2;
    strcpy(msg2.user, "User2");
    strcpy(msg2.text, "Sto bene, volevo dirti che qua fa caldo e freddo, non so se vestirmi a cipolla o ad aglio. Ho molta voglia di parlare, nun teng nient a c fa, tu tutto a posto?");
    msg2.code = 1;

    gui_print(msg2, false);

    Message msg3;
    strcpy(msg3.user, "User1");
    strcpy(msg3.text, "Ah sono contento, anche io sto bene, fin troppo che ti vorrei malmenare");
    msg3.code = 1;
    gui_print(msg3, true);


}
*/