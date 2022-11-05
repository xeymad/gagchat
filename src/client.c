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
#include "tcp_socket.h"
#include "client.h"
#include "queue.h"
#include "gui.h"

TCPSocket *sock;

void *client_message_receiver(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    Message *msg = message_create();
    while (1)
    {
        int ret = tcp_socket_recv_message(sock->sockfd, msg);
        if (ret <= 0)
        {
            fprintf(stderr, "\n\nServer has disconnected anomally\n");
            if (raise(SIGINT) != 0)
            {
                fprintf(stderr, "\n\nFail to send SIG_ERR\n");
            }
        }
        if ((strcmp(msg->user, "Server") == 0) && (msg->code == MSG_SRV_AVLUSR))
        {
            gui_print_list_user(msg->text);
            gui_set_color(Color_Off);
        }
        if (msg->code == MESSAGE)
        {
            TQueue *q = hashTableSearch(args->ht, msg->user);
            if (q == NULL)
            {
                pthread_mutex_lock(args->lock);
                q = queueCreate(QUEUE_SIZE);
                hashTableInsert(args->ht, msg->user, q);
                pthread_mutex_unlock(args->lock);
            }
            if (strcmp(args->selectedUser, msg->user) == 0)
            {
                printf("\r");
                gui_print_message(msg, true);
                pthread_mutex_lock(args->lock);
                queueAdd(q, *msg);
                pthread_mutex_unlock(args->lock);
            }
            else
            {
                // In this case mutex is not required.
                queueAdd(q, *msg);
            }
        }
    }
}

static void client_destroy_connection(int signo)
{
    if (signo == SIGINT)
    {
        printf("\n\nClosing connection\n");
        fflush(stdout);
        tcp_socket_destroy(sock);
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char **argv)
{
    // First try to connect to the specified server.
    sock = tcp_socket_create(CLIENT, "127.0.0.1");
    tcp_socket_client_connect(sock);
    if (signal(SIGINT, client_destroy_connection) == SIG_ERR)
    {
        fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
        exit(1);
    }
    // Client allocates its own sources.
    pthread_mutex_t lock;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        fprintf(stderr, "Mutex init failed with errno %d\n", errno);
        exit(2);
    }
    THashTable *ht = hashTableCreate(LISTENQ);
    char username[USR_MAXLEN];
    Message *msg = message_create();
    // Username creation.
    printf("Please Enter a Username\n");
    int code;
    do
    {
        printf("> ");
        fflush(stdout);
        fgets(username, USR_MAXLEN, stdin);
        username[strcspn(username, " \n")] = '\0';
        message_code_constructor(msg, username, "Nice one this time!", MSG_CLI_CREATE);
        tcp_socket_send_message(sock->sockfd, msg);
        tcp_socket_recv_message(sock->sockfd, msg);
        printf("%s: %s\t%d\n", msg->user, msg->text, msg->code);
        code = msg->code;
    } while (code != MSG_SRV_USRACK);
    // Username creation OK. Print Menu for users.
    char selectedUser[USR_MAXLEN] = "";
    pthread_t tid;
    ThreadArgs *t_args = malloc(sizeof(ThreadArgs));
    t_args->ht = ht;
    t_args->selectedUser = selectedUser;
    t_args->lock = &lock;
    if (pthread_create(&tid, NULL, client_message_receiver, (void *)t_args) != 0)
    {
        fprintf(stderr, "Pthread creation error with errno %d\n", errno);
    }
    char text[TXT_MAXLEN];
    char command[USR_MAXLEN];
    do
    {
        // Gets and parses the command to execute.
        gui_print_menu(username);
        fgets(command, USR_MAXLEN, stdin);
        command[strcspn(command, " \n")] = '\0';
        if (strcmp(command, "show_all")==0)
        {
            message_code_constructor(msg, username, "Nice one this time!", MSG_CLI_LSTUSR);
            tcp_socket_send_message(sock->sockfd, msg);
            continue;
        }
        strncpy(selectedUser, command, strlen(command) + 1);
        // User is selected. Now print last 30 messages, if any
        TQueue *q = hashTableSearch(ht, selectedUser);
        if (q != NULL)
        {
            queuePrint(q, selectedUser);
        }
        else
        {
            pthread_mutex_lock(&lock);
            q = queueCreate(QUEUE_SIZE);
            hashTableInsert(ht, msg->user, q);
            pthread_mutex_unlock(&lock);
        }
        printf("> ");
        fflush(stdout);
        while (strcmp(fgets(text, TXT_MAXLEN, stdin), "__exit\n") != 0)
        {
            text[strcspn(text, "\n")] = '\0';
            message_constructor(msg, selectedUser, text);
            if (tcp_socket_send_message(sock->sockfd, msg) <= 0)
            {
                fprintf(stderr, "\n\nServer has disconnected anomally\n");
                if (raise(SIGINT) != 0)
                {
                    fprintf(stderr, "\n\nFail to send SIG_ERR\n");
                }
            }
            message_constructor(msg, username, text);
            printf("\r\n");
            fflush(stdout);
            gui_print_message(msg, false);
            pthread_mutex_lock(&lock);
            queueAdd(q, *msg);
            pthread_mutex_unlock(&lock);
            printf("> ");
            fflush(stdout);
        }
    } while (1);
}