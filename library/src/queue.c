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

TQueue* queueCreate (int queue_size) {
    TQueue *q = malloc(sizeof(TQueue));
    q->n_element = 0;
    q->front = 0;
    q->back = 0;
    q->size = queue_size;
    q->array = malloc(MSG_MAXLEN * sizeof(Message));
    return q;
}

void queueDestroy (TQueue *q) {
    q->n_element = 0;
    q->back = 0;
    q->n_element = 0;
    free(q->array);
}

void queueAdd (TQueue *q, Message x) {
    q->array[q->back] = malloc(sizeof(Message));
    q->array[q->back]->code = x.code;
    strcpy(q->array[q->back]->text, x.text);
    strcpy(q->array[q->back]->user, x.user);
    q->back = (q->back+1) % q->size;
    if(q->n_element < q->size)
        q->n_element++;
}

Message* queueRemove (TQueue *q) {
    if(q->n_element == 0)
        return NULL;

    Message* x = q->array[q->front];
    q->front = (q->front+1) % q->size;
    q->n_element--;
    return x;
}

Message* queueFront (TQueue *q) {
    return q->array[q->front];
}

int queueIsEmpty (TQueue *q) {
    return q->n_element == 0;
}

void queuePrint(TQueue* q){
    int index = q->front;
    for(int i=0; i<q->n_element; i++)
    {
        gui_print(q->array[index], true);
        index = (index+1)%q->size;
    }
}