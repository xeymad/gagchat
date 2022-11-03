/**
 * @file server.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Server header file
 * @version 0.1
 * @date 2022-10-31
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
#include <pthread.h>
#include "hashtable.h"

/**
 * @brief Struct exchanged by Threads.
 * 
 */
typedef struct SThreadArgs{
    int connection_fd;
    THashTable* ht;
    pthread_mutex_t* lock;
} ThreadArgs;

/**
 * @brief Thread for managing a generic client.
 * 
 */
void* server_manage_client(void* arg);

/**
 * @brief Signal Handler for CTRL+C event.
 */
static void server_destroy_connection(int signo);