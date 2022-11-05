/**
 * @file server.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Server implementation of gagchat.
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
#include "server.h"
#include "tcp_socket.h"
#include "gui.h"

TCPSocket *sock;

static void server_destroy_connection(int signo){
    if(signo == SIGINT){
        printf("\n\nClosing connection\n");
        fflush(stdout);
        tcp_socket_destroy(sock);
        exit(EXIT_SUCCESS);
    }
}

void server_sendToAll(THashTable* ht, TBST tree, Message* message){
    if(tree==NULL) return;
    server_sendToAll(ht,tree->left,message);
    char* user = tree->info;
    int *destination_fd = hashTableSearch(ht,user);
    tcp_socket_send_message(*destination_fd,message);
    server_sendToAll(ht,tree->right,message);
}

void server_sendUsersTo(int connection_fd, TBST users){
    if(users==NULL) return;
    server_sendUsersTo(connection_fd, users->left);
    Message msg;
    message_code_constructor(&msg,"Server",users->info,MSG_SRV_AVLUSR);
    tcp_socket_send_message(connection_fd, &msg);
    server_sendUsersTo(connection_fd, users->right);
}

void* server_manage_client(void* arg){
    ThreadArgs* args = (ThreadArgs*)arg;
    Message* msg = message_create();
    char username[USR_MAXLEN];
    int len_username;
    // Authentication phase.
    do{
        if(tcp_socket_recv_message(args->connection_fd, msg) <=0){
            // Client has disconnected prematurely.
            printf("[ServerInfo]: Client has disconnected prematurely\n");
            close(args->connection_fd);
            message_destroy(msg);
            free(args);
            args = NULL;
            return NULL;
        }
        printf("%s: %s\t%d\n", msg->user, msg->text, msg->code);
        if((msg->code==MSG_CLI_CREATE) && (hashTableSearch(args->ht,msg->user) == NULL))
            break;
        message_code_constructor(msg,"Server","Requested User is not available. Try again.",MSG_SRV_USRNCK);
        tcp_socket_send_message(args->connection_fd, msg);
    }
    while(1);
    // Authentication OK. 
    strncpy(username,msg->user,strlen(msg->user));
    len_username = strlen(username) + 1;
    // Print Server information about accepted username.
    gui_set_color(On_IWhite);
    printf("[ServerInfo]");
    gui_set_color(Default_Color);
    printf(": accepted username ");
    gui_set_color(BRed);
    printf("%s\n",username);
    gui_set_color(Default_Color);
    // Server now inserts User in hashtable and ACKS the client.
    pthread_mutex_lock(args->lock);
    hashTableInsert(args->ht,username,&args->connection_fd);
    *(TBST*)args->tree = BSTinsertI(*(TBST*)args->tree, username);
    pthread_mutex_unlock(args->lock);
    message_code_constructor(msg,"Server","User Accepted",MSG_SRV_USRACK);
    tcp_socket_send_message(args->connection_fd, msg);
    // User insert ok. Now let's dispatch.
    do{
        if(tcp_socket_recv_message(args->connection_fd, msg) <=0){
            // Client has disconnected. Free resources and remove occurrance from hashtable.
            printf("[ServerInfo]: Disconnecting user %s\n", username);
            pthread_mutex_lock(args->lock);
            hashTableDelete(args->ht,username);
            *(TBST*)args->tree = BSTdeleteI(*(TBST*)args->tree, username);
            pthread_mutex_unlock(args->lock);
            close(args->connection_fd);
            message_destroy(msg);
            free(args);
            args = NULL;
            return NULL;
        }
        int *destination_fd;
        printf("%s: %s\t%d\n", msg->user, msg->text, msg->code);
        if(msg->code==MESSAGE){
            if(strcmp(msg->user, "all") == 0){
                strncpy(msg->user,username,len_username);
                server_sendToAll(args->ht, *(TBST*)args->tree, msg);
                continue;
            }
            destination_fd = hashTableSearch(args->ht, msg->user);
            if(destination_fd == NULL){
                printf("[ServerInfo]: User %s unreachable\n",msg->user);
                message_code_constructor(msg,"Server","Requested user not reacheable",MSG_SRV_USRNRC);
                tcp_socket_send_message(args->connection_fd,msg);
            }
            else{
                strncpy(msg->user,username,len_username);
                tcp_socket_send_message(*destination_fd,msg);
            }
        }
        else if(msg->code==MSG_CLI_LSTUSR){
            server_sendUsersTo(args->connection_fd, *(TBST*)args->tree);
        }
    } while (1);
    close(args->connection_fd);
}


int main(int argc, char **argv)
{
    pthread_t tid;
    pthread_mutex_t lock;
    THashTable* ht = hashTableCreate(LISTENQ);
    TBST bst = BSTcreate();
    hashTableInsert(ht,"Server", &ht);
    hashTableInsert(ht,"all", &bst);
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
        gui_set_color(On_IWhite);
        printf("[ServerInfo]");
        gui_set_color(Default_Color);
        printf(": request with connection_fd %d\n",connection_fd);
        fflush(stdout);
        ThreadArgs* t_args = malloc(sizeof(ThreadArgs));
        if(t_args==NULL){
            fprintf(stderr, "No such memory to allocate\n");
            continue;
        }
        t_args->connection_fd = connection_fd;
        t_args->ht = ht;
        t_args->tree = &bst;
        t_args->lock = &lock;
        if(pthread_create(&tid, NULL, server_manage_client, (void *)t_args) != 0){
            fprintf(stderr, "Pthread creation error with errno %d\n", errno);
        }
    }
    // destroy socket
    tcp_socket_destroy(sock);
}
