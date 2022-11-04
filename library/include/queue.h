/**
 * @file queue.h
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

#ifndef QUEUE_H
#define QUEUE_H

#include "message.h"

/**
 * @brief Struct of the queue
 * 
 */
typedef struct {
    int n_element; // numero di elementi
    int front; // indice front
    int back; // indice back
    int size;
    Message **array; 
} TQueue;

TQueue* queueCreate();

void queueDestroy (TQueue *q);

void queueAdd (TQueue *q, Message x);

Message* queueRemove (TQueue *q);

Message* queueFront (TQueue *q);

int queueIsEmpty (TQueue *q);

void queuePrint(TQueue* q, char* user_sender);

#endif