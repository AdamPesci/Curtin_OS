/* ready_queue.c
*
* This file contains the methods required for using a linked list as a queue
* 
* Author: Adam Camer-Pesci
* 
* Written: 22/04/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "ready_queue.h"

/* 
* Get first item from linked list
* See linked_list.c peekFirst() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*/
Data_t peek(Queue_t *queue)
{
    Data_t ret = peekFirst(queue->list);
    return ret;
}

/* 
* Remove first item from linked list
* See linked_list.c removeFirst() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*/
void dequeue(Queue_t *queue)
{
    /* de-allocate memory used for Task_t struct */
    Node_t *current = queue->list->head;
    Task_t *del = (Task_t *)current->value.data;
    free(del);
    /* let removeFirst method handle the rest */
    removeFirst(queue->list);
    queue->numElem--;
}

/* 
* Add new item to end of the list
* See linked_list.c insertLast() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*       inValue: some data we want to put into queue
*/
void enqueue(Queue_t *queue, void *inValue)
{
    /* insert element at end of queue, increment number of elems */
    insertLast(queue->list, inValue);
    queue->numElem++;
}

/* 
* Construct an empty queue with size m and initializes number of elements to 0
* See linked_list.c makeList() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*       m: the max size of the queue
*/
void makeQueue(Queue_t *queue, int m)
{
    /* initialize and allocate memory for queue member fields */
    queue->maxSize = m;
    queue->numElem = 0;
    queue->list = (LinkedList_t *)malloc(sizeof(LinkedList_t));
    makeList(queue->list);
}

/* 
* Free the queue
* See linked_list.c FreeList() documentation for method details
* freeQueue also free's the malloc'd queue
* FIELDS:
*       queue: a pointer to a queue struct
*/
void freeQueue(Queue_t *queue)
{
    /* free all Task_t structs stored in linked list */
    Node_t *current = queue->list->head;
    Node_t *next;
    while (current != NULL)
    {
        next = current->next;
        Task_t *del = (Task_t *)current->value.data;
        free(del);
        current = next;
    }
    /* let freeList handle the rest */
    freeList(queue->list);
    free(queue);
}

/* 
* Check if queue is empty 
* is empty when queue->numElem == 0;
* FIELDS:
*       queue: a pointer to a queue struct
*
* RETURN: 1 if empty | 0 if not empty
*/
int qEmpty(Queue_t *queue)
{
    int isEmpty = 0;
    if (queue->numElem == 0)
    {
        isEmpty = 1;
    }
    return isEmpty;
}

/* 
* Check if queue is full
* is full when queue->numElem == queue->maxSize;
* FIELDS:
*       queue: a pointer to a queue struct
*
* RETURN: 1 if full | 0 if not full
*/
int qFull(Queue_t *queue)
{
    int isFull = 0;
    if (queue->numElem == queue->maxSize)
    {
        isFull = 1;
    }
    return isFull;
}