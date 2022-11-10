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

/**
 * @brief Thread listener and management
 *
 * @param arg ThreadArgs var containing all the necessary information
 * @return void*
 */
void *client_message_receiver(void *arg)
{
    // Cast the arg to a pointer of ThreadArgs
    ThreadArgs *args = (ThreadArgs *)arg;

    // Create a message
    Message *msg = message_create();

    // Do forever
    while (1)
    {
        // Wait for a message
        int ret = tcp_socket_recv_message(sock->sockfd, msg);
        if (ret <= 0)
        {
            fprintf(stderr, "\n\nServer has disconnected anomally\n");
            if (raise(SIGINT) != 0)
            {
                fprintf(stderr, "\n\nFail to send SIG_ERR\n");
            }
        }

        // Server info about users
        if ((strcmp(msg->user, "Server") == 0))
        {
            // Show an user after require the list of users
            if (msg->code == MSG_SRV_LSTUSR)
            {
                // If the user is not the user client
                if (strcmp(msg->text, args->clientUser) != 0)
                {
                    gui_print_list_user(msg->text);
                }
            }
            // End of the user list
            else if (msg->code == MSG_END_LSTUSR)
            {
                gui_print_list_users_footer();
            }
            // If a user is not available
            else if (msg->code == MSG_SRV_USR_IS_NAVL)
            {
                // deselect it
                strncpy(args->selectedUser, "", 1);

                // Go to the homepage
                if (*args->menu == GUI_SHOW_USR)
                {
                    *args->menu = GUI_SHOW_USR;
                    gui_print_list_users_header();
                    message_code_constructor(msg, msg->user, "Retrieve all Users", MSG_CLI_LSTUSR);
                    tcp_socket_send_message(sock->sockfd, msg);
                }
                else if (*args->menu == GUI_MENU)
                {
                    gui_print_menu(args->clientUser);
                }
            }
            // If a user is available
            else if (msg->code == MSG_SRV_USR_IS_AVL)
            {
                // Select the user and go to the page that show the messages
                strncpy(args->selectedUser, msg->text, strlen(msg->text) + 1);
                *args->menu = GUI_SHOW_MSG;
                gui_clear_Screen();
                printf("Press any command\n");
            }
            // If a user become unreachble
            else if (msg->code == MSG_SRV_USRNRC && (strcmp(args->selectedUser, msg->text) == 0))
            {
                // Go to or updata the page "all user"
                strcpy(args->selectedUser, "");
                if (*args->menu == GUI_SHOW_MSG || *args->menu == GUI_SHOW_USR)
                {
                    *args->menu = GUI_MENU;
                    gui_clear_Screen();
                    printf("%s disconnected!\nPress any key to return to the menu: \n", msg->text);
                }
            }
            continue;
        }

        // If there is a new user and the client lies in the "show all" pages
        // then reload the users list
        if ((msg->code == MSG_SRV_NEW_USR) && *args->menu == GUI_SHOW_USR)
        {
            gui_print_list_users_header();
            message_code_constructor(msg, args->clientUser, "Retrieve all Users", MSG_CLI_LSTUSR);
            tcp_socket_send_message(sock->sockfd, msg);
        }

        // Message info
        else if (msg->code == MESSAGE)
        {

            // Search the user in the hashtable
            TQueue *q = hashTableSearch(args->ht, msg->user);

            // If is a new user
            if (q == NULL)
            {
                // create a queue and insert it in the hashtable
                pthread_mutex_lock(args->lock);
                q = queueCreate(MSG_HISTORY_MAXLEN);
                hashTableInsert(args->ht, msg->user, q);
                pthread_mutex_unlock(args->lock);

                // If the client lies in the "show_all" pages, then update the user list
                if (*args->menu == GUI_SHOW_USR)
                {
                    gui_print_list_users_header();
                    message_code_constructor(msg, args->clientUser, "Retrieve all Users", MSG_CLI_LSTUSR);
                    tcp_socket_send_message(sock->sockfd, msg);
                }
            }
            // If the user is the selected one
            if (strcmp(args->selectedUser, msg->user) == 0)
            {
                printf("\r");
                gui_print_message(msg, true);
                pthread_mutex_lock(args->lock);
                queueAdd(q, *msg);
                pthread_mutex_unlock(args->lock);
            }
            // If is selected anothe user, save only in the queue
            else
            {
                queueAdd(q, *msg);
            }
        }
        // If the message is for all (broadcast chat)
        else if (msg->code == MSG_SRV_ALL)
        {
            // Search the user in the hashtable
            TQueue *q = hashTableSearch(args->ht, "all");

            // If is a new user
            if (q == NULL)
            {
                // create a queue and insert it in the hashtable
                pthread_mutex_lock(args->lock);
                q = queueCreate(MSG_HISTORY_MAXLEN);
                hashTableInsert(args->ht, "all", q);
                pthread_mutex_unlock(args->lock);

                // If the client lies in the "show_all" pages, then update the user list
                if (*args->menu == GUI_SHOW_USR)
                {
                    gui_print_list_users_header();
                    message_code_constructor(msg, args->clientUser, "Retrieve all Users", MSG_CLI_LSTUSR);
                    tcp_socket_send_message(sock->sockfd, msg);
                }
            }

            // If the user selected is "all", this means that is a broadcast message
            if (strcmp(args->selectedUser, "all") == 0)
            {
                printf("\r");
                gui_print_message(msg, true);
                pthread_mutex_lock(args->lock);
                queueAdd(q, *msg);
                pthread_mutex_unlock(args->lock);
            }
            else
            {
                queueAdd(q, *msg);
            }
        }
    }
}

/**
 * @brief Routine for an Asynchronous Signal - Destroy the connection
 *
 * @param signo Signal type
 */
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
    if (argc != 2)
    {
        fprintf(stderr, "Usage: TCPClient <IP address of the server>\n");
        exit(1);
    }

    /* Create the tcp socket in CLIENT MODE using the server address passed by terminal */
    sock = tcp_socket_create(CLIENT, argv[1]);
    tcp_socket_client_connect(sock);

    /* Enable the management of the SIGNAL SIGINT*/
    if (signal(SIGINT, client_destroy_connection) == SIG_ERR)
    {
        fprintf(stderr, "Can't catch SIGINT: %s", strerror(errno));
        // Raise the signal SIGINT for destroy the tcp connection
        if (raise(SIGINT) != 0)
        {
            fprintf(stderr, "\n\nFail to send SIG_ERR\n");
            exit(2);
        }
    }

    // Client allocates its own sources.
    pthread_mutex_t lock;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        fprintf(stderr, "Mutex init failed with errno %d\n", errno);
        // Raise the signal SIGINT for destroy the tcp connection
        if (raise(SIGINT) != 0)
        {
            fprintf(stderr, "\n\nFail to send SIG_ERR\n");
            exit(3);
        }
    }

    // Allocate the hashTable for the users
    THashTable *ht = hashTableCreate(LISTENQ);

    char username[USR_MAXLEN];
    Message *msg_login = message_create();
    // Username creation.
    gui_clear_Screen();
    printf("Please Enter a Username\n");
    do
    {
        printf("> ");
        fflush(stdout);
        fgets(username, USR_MAXLEN, stdin);
        username[strcspn(username, " \n")] = '\0';
        message_code_constructor(msg_login, username, "Nice one this time!", MSG_CLI_CREATE);
        tcp_socket_send_message(sock->sockfd, msg_login);
        tcp_socket_recv_message(sock->sockfd, msg_login);
        printf("%s: %s\t%d\n", msg_login->user, msg_login->text, msg_login->code);
    } while (msg_login->code != MSG_SRV_USRACK);

    // Username creation OK. Print Menu for users.
    // Istance a new thread listener for the user
    // char selectedUser[USR_MAXLEN] = "";
    pthread_t tid;
    char *selectedUser = malloc(USR_MAXLEN * sizeof(char));
    ThreadArgs *t_args = malloc(sizeof(ThreadArgs));
    u_int8_t menu = GUI_MENU;
    t_args->ht = ht;
    t_args->selectedUser = selectedUser;
    t_args->clientUser = username;
    t_args->menu = &menu;
    t_args->lock = &lock;
    if (pthread_create(&tid, NULL, client_message_receiver, (void *)t_args) != 0)
    {
        fprintf(stderr, "Pthread creation error with errno %d\n", errno);
    }

    // User navigation on the menu
    gui_print_menu(username);

    // Istance the message, text and command vars
    Message *msg = message_create();
    char text[TXT_MAXLEN];
    char command[USR_MAXLEN];
    do
    {
        // Gets and parses the command to execute.
        fgets(command, USR_MAXLEN, stdin);
        command[strcspn(command, " \n")] = '\0';

        if (strlen(command) == 0)
        {
            if (menu == GUI_MENU)
            {
                gui_print_menu(username);

                // Do nothing
                continue;
            }
        }

        // Do stuff according to the actual page
        if (menu == GUI_MENU)
        {
            // If the command is "show_all"
            if (strcmp(command, "show_all") == 0)
            {
                // Open the page "show_all" that show all the user active
                gui_print_list_users_header();
                message_code_constructor(msg, username, "Retrieve all Users", MSG_CLI_LSTUSR);
                tcp_socket_send_message(sock->sockfd, msg);
                menu = GUI_SHOW_USR;
            }
            // Otherwise send the username that the client want to comunicate
            else
            {
                message_code_constructor(msg, command, "", MSG_CLI_USR);
                if (tcp_socket_send_message(sock->sockfd, msg) <= 0)
                {
                    fprintf(stderr, "\n\nServer has disconnected anomally\n");
                    if (raise(SIGINT) != 0)
                    {
                        fprintf(stderr, "\n\nFail to send SIG_ERR\n");
                    }
                }
            }
        }
        else if (menu == GUI_SHOW_USR)
        {
            // If the command is "__menu" return to the homepage
            if (strcmp(command, "__menu") == 0)
            {
                menu = GUI_MENU;
                gui_print_menu(username);
                strncpy(selectedUser, "", 1);
                continue;
            }
            // Otherwise send the username that the client want to comunicate
            message_code_constructor(msg, command, "", MSG_CLI_USR);
            if (tcp_socket_send_message(sock->sockfd, msg) <= 0)
            {
                fprintf(stderr, "\n\nServer has disconnected anomally\n");
                if (raise(SIGINT) != 0)
                {
                    fprintf(stderr, "\n\nFail to send SIG_ERR\n");
                }
            }
        }
        else if (menu == GUI_SHOW_MSG)
        {
            gui_clear_Screen();

            // User is selected.
            // Now print last MSG_HISTORY_MAXLEN messages
            // if the user is a new chat, then create a queue of message
            TQueue *q = hashTableSearch(ht, selectedUser);
            if (q != NULL)
            {
                queuePrint(q, username);
            }
            else
            {
                pthread_mutex_lock(&lock);
                q = queueCreate(MSG_HISTORY_MAXLEN);
                hashTableInsert(ht, msg->user, q);
                pthread_mutex_unlock(&lock);
            }

            // While the client insert "__exit" send message to the selected user
            while (strcmp(fgets(text, TXT_MAXLEN, stdin), "__exit\n") != 0 && menu == GUI_SHOW_MSG)
            {

                // Remove the last row
                printf("\033[1A");
                text[strcspn(text, "\n")] = '\0';

                if (strlen(text) == 0)
                {
                    // Do nothing
                    continue;
                }

                // Construct the message and the send it
                message_constructor(msg, selectedUser, text);
                if (tcp_socket_send_message(sock->sockfd, msg) <= 0)
                {
                    fprintf(stderr, "\n\nServer has disconnected anomally\n");
                    if (raise(SIGINT) != 0)
                    {
                        fprintf(stderr, "\n\nFail to send SIG_ERR\n");
                    }
                }

                // Print the self message
                message_constructor(msg, username, text);
                printf("\r");
                fflush(stdout);
                gui_print_message(msg, false);

                // Acquire mutex of the queue
                pthread_mutex_lock(&lock);
                queueAdd(q, *msg);
                pthread_mutex_unlock(&lock);

                fflush(stdout);
            }

            // Exit to the menu
            menu = GUI_MENU;
            gui_print_menu(username);
            strncpy(selectedUser, "", 1);
        }

    } while (1);
}