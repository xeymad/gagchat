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

int server_check_username_exists(char *username){
    //TODO: insert server logic.
    return 0;
}

void* server_manage_client(void* arg){
    int rc;
    int connfd = *((int*)arg);
    Message* msg;
    char username[USR_MAXLEN];
    // Authentication phase.
    do{
        msg = tcp_socket_recv_message(connfd);
        printf("%s: %s\n%d\n", msg->user, msg->text, msg->code);
        if(!server_check_username_exists(msg->user)){
            strncpy(username,msg->user,strlen(msg->user));
            break;
        }
    }
    while(1);
    printf("Server has confirmed username %s\n",username);
    close(connfd);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    TCPSocket *sock = tcp_socket_create(SERVER, "");
    tcp_socket_server_listen(sock);
    printf("%s\n", "Server running...waiting for connections.");
    while (1)
    {
        int connfd = tcp_socket_server_accept(sock);
        printf("%s\n", "Received request...");
        fflush(stdout);
        if(pthread_create(&tid, NULL, server_manage_client, &connfd) != 0){
            fprintf(stderr, "Pthread creation error with errno %d\n", errno);
        }
    }
    // destroy socket
    tcp_socket_destroy(sock);
}
