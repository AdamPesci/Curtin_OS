/*
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
*/
Data_t peek(Queue_t *queue)
{
    Data_t ret = peekFirst(queue->list);
    return ret;
}

/* 
* Remove first item from linked list, free the Task_t struct
* See linked_list.c removeLast() documentation for method details
*/
void dequeue(Queue_t *queue)
{
    Node_t *current = queue->list->head;

    Task_t *del = (Task_t *)current->value.data;
    free(del);

    removeFirst(queue->list);
    queue->numElem--;
}

/* 
* Add new item to end of the list
* See linked_list.c insertLast() documentation for method details
*/
void enqueue(Queue_t *queue, void *inValue)
{

    insertLast(queue->list, inValue);
    queue->numElem++;
}

/* 
* Construct an empty queue with size m and initializes number of elements to 0
* See linked_list.c makeList() documentation for method details
*/
void makeQueue(Queue_t *queue, int m)
{
    queue->maxSize = m;
    queue->numElem = 0;
    queue->list = (LinkedList_t *)malloc(sizeof(LinkedList_t));
    makeList(queue->list);
}

/* 
* Free the queue free's all of the Task_t structs before list is freed
* See linked_list.c FreeList() documentation for method details
* freeQueue also free's the malloc'd queue
*/
void freeQueue(Queue_t *queue)
{
    Node_t *current = queue->list->head;
    Node_t *next;
    while (current != NULL)
    {
        next = current->next;
        Task_t *del = (Task_t *)current->value.data;
        free(del);
        current = next;
    }
    freeList(queue->list);
    free(queue);
}

/* 
* Free the queue
* See linked_list.c FreeList() documentation for method details
* freeQueue also free's the malloc'd queue
*/
int size(Queue_t *queue)
{
    return queue->maxSize;
}

/* 
* Check if queue is empty 
* is empty when queue->numElem == 0;
* returns 0 if empty 1 if not empty
*/
int qEmpty(Queue_t *queue)
{
    int isEmpty = 1;
    if (queue->numElem == 0)
    {
        isEmpty = 0;
    }
    return isEmpty;
}