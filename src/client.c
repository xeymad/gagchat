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
#include <pthread.h>
#include "tcp_socket.h"



int main(int argc, char** argv){
    char username[USR_MAXLEN];
    //Note: the following code was tested with 'echoServer.c'
    Message* msg = message_create();
    TCPSocket* sock = tcp_socket_create(CLIENT,"127.0.0.1");
    tcp_socket_client_connect(sock);
    // Username creation.
    printf("Please Enter a Username\n");
    int code;
    do{
        printf(">");
        fflush(stdout);
        fgets(username,USR_MAXLEN,stdin);
        message_code_constructor(msg, username,"Nice one this time!",MSG_CLI_CREATE);
        printf("%s: %s\t%d\n",msg->user,msg->text,msg->code);
        tcp_socket_send_message(sock->sockfd,msg);
        tcp_socket_recv_message(sock->sockfd,msg);
        printf("%s: %s\t%d\n",msg->user,msg->text,msg->code);
        code = msg->code;
    } while(code!=MSG_SRV_USRACK);
    //tcp_socket_destroy(sock);
    message_destroy(msg);
    return EXIT_SUCCESS;
}