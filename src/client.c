/**
 * @file client.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Client Implementation of gagchat
 * @version 0.1
 * @date 2022-10-28
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
#include "message.h"

int main(int argc, char** argv){
    Message* msg = message_err_constructor("userName","nice one this time!",3);
    printf("%s: %s\n%d\n",msg->user,msg->text,msg->code);
    message_destroy(msg);
    return EXIT_SUCCESS;
}