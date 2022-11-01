/**
 * @file server.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief
 * @version 0.1
 * @date 2022-10-30
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
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include "tcp_socket.h"
#include "server.h"
#include "hashtable.h"

THashTable* ht;

int server_check_username_exists(char *username){
    //TODO: insert mutex.
    return (hashTableSearch(ht,username)!=NULL);
}

void* server_manage_client(void* arg){
    int rc;
    int connfd = (int)arg;
    Message* msg = message_create();
    char username[USR_MAXLEN];
    // Authentication phase.
    do{
        tcp_socket_recv_message(connfd, msg);
        printf("%s: %s\t%d\n", msg->user, msg->text, msg->code);
        if(!server_check_username_exists(msg->user)){
            break;
        }
        message_code_constructor(msg,"Server","Requested User is not available. Try again.",MSG_SRV_USRNCK);
        tcp_socket_send_message(connfd, msg);
    }
    while(1);
    // Authentication OK. Server now inserts User in hashtable.
    strncpy(username,msg->user,strlen(msg->user));
    message_code_constructor(msg,"Server","User Accepted",MSG_SRV_USRACK);
    printf("Server has accepted username %s\n",username);
    tcp_socket_send_message(connfd, msg);
    hashTableInsert(ht,username,connfd);
    close(connfd);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    ht = hashTableCreate(LISTENQ);
    TCPSocket *sock = tcp_socket_create(SERVER, "");
    tcp_socket_server_listen(sock);
    printf("%s\n", "Server running...waiting for connections.");
    int connfd;
    while (1)
    {
        if((connfd = tcp_socket_server_accept(sock)) < 0){
            fprintf(stderr, "Accept connection error with errno %d\n", errno);
            continue;
        }
        printf("Received request with connfd %d\n",connfd);
        fflush(stdout);
        if(pthread_create(&tid, NULL, server_manage_client, (void *)connfd) != 0){
            fprintf(stderr, "Pthread creation error with errno %d\n", errno);
        }
    }
    // destroy socket
    tcp_socket_destroy(sock);
}
