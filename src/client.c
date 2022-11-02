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
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include "tcp_socket.h"

TCPSocket* sock;

void* client_message_receiver(void *args){
    Message* msg;
    while(1){
        tcp_socket_recv_message(sock->sockfd, msg);
        printf("\033[1;31m");
        printf("%s: %s\t%d\n",msg->user,msg->text,msg->code);
        printf("\033[0m\n");
    }
}

static void client_destroy_connection(int signo){
    if(signo == SIGINT){
        printf("\n\nClosing connection\n");
        fflush(stdout);
        tcp_socket_destroy(sock);
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char** argv){
    sock = tcp_socket_create(CLIENT,"127.0.0.1");
    tcp_socket_client_connect(sock);
    if (signal(SIGINT, client_destroy_connection) == SIG_ERR) {
		fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
		exit(1);
	}
    char username[USR_MAXLEN];
    //Note: the following code was tested with 'echoServer.c'
    Message* msg = message_create();
    // Username creation.
    printf("Please Enter a Username\n");
    int code;
    do{
        printf(">");
        fflush(stdout);
        fgets(username,USR_MAXLEN,stdin);
        username[strcspn(username, " \n")] = '\0';
        message_code_constructor(msg, username,"Nice one this time!", MSG_CLI_CREATE);
        tcp_socket_send_message(sock->sockfd,msg);
        tcp_socket_recv_message(sock->sockfd,msg);
        printf("%s: %s\t%d\n",msg->user,msg->text,msg->code);
        code = msg->code;
    } while(code!=MSG_SRV_USRACK);
    pthread_t tid;
    if(pthread_create(&tid, NULL, client_message_receiver, NULL) != 0){
        fprintf(stderr, "Pthread creation error with errno %d\n", errno);
    }
    pthread_join(tid,NULL);
    message_destroy(msg);
    return EXIT_SUCCESS;
}