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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "tcp_socket.h"
#include "server.h"

TCPSocket *sock;

static void server_destroy_connection(int signo){
    if(signo == SIGINT){
        printf("\n\nClosing connection\n");
        fflush(stdout);
        tcp_socket_destroy(sock);
        exit(EXIT_SUCCESS);
    }
}

void* server_manage_client(void* arg){
    int rc;
    ThreadArgs* args = (ThreadArgs*)arg;
    Message* msg = message_create();
    char username[USR_MAXLEN];
    // Authentication phase.
    do{
        tcp_socket_recv_message(args->connection_fd, msg);
        printf("%s: %s\t%d\n", msg->user, msg->text, msg->code);
        if((msg->code==MSG_CLI_CREATE) && (hashTableSearch(args->ht,msg->user) == NULL))
            break;
        message_code_constructor(msg,"Server","Requested User is not available. Try again.",MSG_SRV_USRNCK);
        tcp_socket_send_message(args->connection_fd, msg);
    }
    while(1);
    // Authentication OK. Server now inserts User in hashtable.
    strncpy(username,msg->user,strlen(msg->user));
    message_code_constructor(msg,"Server","User Accepted",MSG_SRV_USRACK);
    printf("Server has accepted username %s\n",username);
    tcp_socket_send_message(args->connection_fd, msg);
    pthread_mutex_lock(args->lock);
    hashTableInsert(args->ht,username,&args->connection_fd);
    pthread_mutex_unlock(args->lock);
    while (1)
    {
        pause();
    }
    close(args->connection_fd);
}

int main(int argc, char **argv)
{
    pthread_t tid;
    pthread_mutex_t lock;
    THashTable* ht = hashTableCreate(LISTENQ);
    sock = tcp_socket_create(SERVER, "");
    tcp_socket_server_listen(sock);
    printf("%s\n", "Server running...waiting for connections.");
    if (signal(SIGINT, server_destroy_connection) == SIG_ERR) {
		fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
		exit(1);
	}
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        fprintf(stderr,"Mutex init failed with errno %d\n", errno);
        exit(2);
    }
    int connection_fd;
    while (1)
    {
        if((connection_fd = tcp_socket_server_accept(sock)) < 0){
            fprintf(stderr, "Accept connection error with errno %d\n", errno);
            continue;
        }
        printf("Received request with connfd %d\n",connection_fd);
        fflush(stdout);
        ThreadArgs* t_args = malloc(sizeof(ThreadArgs));
        t_args->connection_fd = connection_fd;
        t_args->ht = ht;
        t_args->lock = &lock;
        if(pthread_create(&tid, NULL, server_manage_client, (void *)t_args) != 0){
            fprintf(stderr, "Pthread creation error with errno %d\n", errno);
        }
    }
    // destroy socket
    tcp_socket_destroy(sock);
}
