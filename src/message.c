/**
 * @file message.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
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
#include "message.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Message* message_constructor(char *user, char* text){
    Message* msg = malloc(sizeof(Message));
    assert(msg != NULL);
    int len_user = strlen(user);
    assert(len_user<USR_MAXLEN);
    int len_text = strlen(text);
    assert(len_text<TXT_MAXLEN);
    strncpy(msg->user,user,len_user);
    strncpy(msg->text,text,len_text);
    msg->code = 0;
    return msg;
}

Message* message_err_constructor(char *user, char* text, int code){
    Message* msg = malloc(sizeof(Message));
    assert(msg != NULL);
    int len_user = strlen(user);
    assert(len_user<USR_MAXLEN);
    int len_text = strlen(text);
    assert(len_text<TXT_MAXLEN);
    strncpy(msg->user,user,len_user);
    strncpy(msg->text,text,len_text);
    msg->code = code;
    return msg;
}

void message_destroy(Message* message){
    free(message);
}