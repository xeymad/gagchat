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
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "tcp_socket.h"
#include "client.h"
#include "queue.h"
#include "gui.h"


TCPSocket* sock;

void* client_message_receiver(void *arg){
    ThreadArgs* args = (ThreadArgs*)arg;
    Message* msg = message_create();
    while(1){  
        int ret = tcp_socket_recv_message(sock->sockfd, msg);
        if(ret<=0){
            fprintf(stderr, "\n\nServer has disconnected anomally\n");
            if(raise(SIGINT) != 0)
            {
                fprintf(stderr, "\n\nFail to send SIG_ERR\n");
            }
        }
        if((strcmp(msg->user,"Server")==0) && (msg->code==MSG_SRV_AVLUSR)){
            gui_print_list_user(msg->text);
        }
        TQueue* q = hashTableSearch(args->ht,msg->user);
        if(q == NULL){
            q = queueCreate(QUEUE_SIZE);
            hashTableInsert(args->ht,msg->user,q);
        }
        queueAdd(q,*msg);
        if(strcmp(args->selectedUser,msg->user)==0){
            gui_print_message(msg,true);
        }
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
    THashTable* ht = hashTableCreate(LISTENQ);
    char username[USR_MAXLEN];
    //Note: the following code was tested with 'echoServer.c'
    Message* msg = message_create();
    // Username creation.
    printf("Please Enter a Username\n");
    int code;
    do{
        printf("> ");
        fflush(stdout);
        fgets(username,USR_MAXLEN,stdin);
        username[strcspn(username, " \n")] = '\0';
        message_code_constructor(msg, username,"Nice one this time!", MSG_CLI_CREATE);
        tcp_socket_send_message(sock->sockfd,msg);
        tcp_socket_recv_message(sock->sockfd,msg);
        printf("%s: %s\t%d\n",msg->user,msg->text,msg->code);
        code = msg->code;
    } while(code!=MSG_SRV_USRACK);
    // Username creation OK.
    gui_print_menu(username);
    char selectedUser[USR_MAXLEN] = "";
    pthread_t tid;
    ThreadArgs* t_args = malloc(sizeof(ThreadArgs));
    t_args->ht = ht; 
    t_args->selectedUser = selectedUser;
    if(pthread_create(&tid, NULL, client_message_receiver, (void *)t_args) != 0){
        fprintf(stderr, "Pthread creation error with errno %d\n", errno);
    }
    message_code_constructor(msg, username,"Nice one this time!", MSG_CLI_LSTUSR);
    tcp_socket_send_message(sock->sockfd,msg);
    char text[TXT_MAXLEN];
    char selection[USR_MAXLEN];
    do{
        printf("\rPlease insert user to send message\n");
        printf("> ");
        fflush(stdout);
        fgets(selection,USR_MAXLEN,stdin);
        //printf("Please insert text\n");
        printf("> ");
        fflush(stdout);
        selection[strcspn(selection, " \n")] = '\0';
        strncpy(selectedUser,selection,strlen(selection)+1);

        TQueue* q = hashTableSearch(ht,msg->user);
        if(q!=NULL)
            queuePrint(q,selectedUser);
        while(strcmp(fgets(text,TXT_MAXLEN,stdin),"exit\n")!= 0){
            text[strcspn(text, "\n")] = '\0';
            message_constructor(msg,selection,text);
            if(tcp_socket_send_message(sock->sockfd,msg) <= 0){
                fprintf(stderr, "\n\nServer has disconnected anomally\n");
                if(raise(SIGINT) != 0)
                {
                    fprintf(stderr, "\n\nFail to send SIG_ERR\n");
                }
            }
            message_constructor(msg,username,text);
            gui_print_message(msg,false);
        }
    } while(1);
}