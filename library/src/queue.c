/**
 * @file queue.c
 * @author Gianluca (g.canzolino3@studenti.unisa.it)
 * @brief
 * @version 0.1
 * @date 2022-11-03
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

/*
 * TQueue: implementazione di una coda attraverso un array dinamico
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "queue.h"
#include "gui.h"

/**
 * @brief Create a new queue
 *
 * @return TQueue* a new istance of queue
 */
TQueue *queueCreate(int queue_size)
{
    TQueue *q = malloc(sizeof(TQueue));
    q->n_element = 0;
    q->front = 0;
    q->back = 0;
    q->size = queue_size;
    q->array = malloc(MSG_HISTORY_MAXLEN * sizeof(Message));
    return q;
}

/**
 * @brief Destroy a queue
 *
 * @param q Pointer of selected queue
 */
void queueDestroy(TQueue *q)
{
    q->n_element = 0;
    q->back = 0;
    q->n_element = 0;
    free(q->array);
}

/**
 * @brief Add a new message to the queue
 *
 * @param q Pointer of the queue
 * @param x Message to insert in the queue
 */
void queueAdd(TQueue *q, Message x)
{
    q->array[q->back] = malloc(sizeof(Message));
    q->array[q->back]->code = x.code;
    strcpy(q->array[q->back]->text, x.text);
    strcpy(q->array[q->back]->user, x.user);
    q->back = (q->back + 1) % q->size;
    if (q->n_element < q->size)
        q->n_element++;
}

/**
 * @brief Remove the element at the front of the queue
 *
 * @param q Pointer of the queue
 * @return Message* Pointer of the message at the front of the queue
 */
Message *queueRemove(TQueue *q)
{
    if (q->n_element == 0)
        return NULL;

    Message *x = q->array[q->front];
    q->front = (q->front + 1) % q->size;
    q->n_element--;
    return x;
}

/**
 * @brief Return the element at the front of the queue
 *
 * @param q Pointer of the queue
 * @return Message* Message* Pointer of the message at the front of the queue
 */
Message *queueFront(TQueue *q)
{
    return q->array[q->front];
}

/**
 * @brief Return if the queue is empty
 *
 * @param q Pointer of the queue
 * @return int 1 if is empty, 0 otherwise
 */
int queueIsEmpty(TQueue *q)
{
    return q->n_element == 0;
}

/**
 * @brief Print all the element in the queue from the front
 *
 * @param q Pointer of the queue
 * @param username Pointer to the client user
 */
void queuePrint(TQueue *q, char *username)
{
    int index = q->front;
    for (int i = 0; i < q->n_element; i++)
    {
        gui_print_message(q->array[index], strcmp(q->array[index]->user, username) != 0);
        index = (index + 1) % q->size;
    }
}