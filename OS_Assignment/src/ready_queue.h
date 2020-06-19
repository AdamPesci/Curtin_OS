#pragma once
/* ready_queue.h
*
* This file contains the method declarations for ready_queue.c
* 
* Author: Adam Camer-Pesci
* 
* Written: 22/04/2019
*/

/*
*TYPEDEF:Struct Queue
*FIELDS: maxSize: The maximum size of the queue 
         numElem: The current number of elements in the list
         list: A pointer to a linked list
*/
typedef struct Queue
{
    int maxSize;
    int numElem;
    LinkedList_t *list;
} Queue_t;

/*
*TYPEDEF: Struct Task
*FIELDS: taskNum: The number of the task
*        burstTime: The burst time of the task
         arrivalTime: an array to hold the string representation of current time (See getTime() Method)
*/
typedef struct Task
{
    int taskNum;
    int burstTime;
    char arrivalTime[9];
    char serviceTime[9];
    char completionTime[9];
} Task_t;

/* 
* Get first item from linked list
* See linked_list.c peekFirst() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*/
Data_t peek(Queue_t *queue);

/* 
* Remove first item from linked list
* See linked_list.c removeFirst() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*/
void dequeue(Queue_t *queue);

/* 
* Add new item to end of the list
* See linked_list.c insertLast() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*       inValue: some data we want to put into queue
*/
void enqueue(Queue_t *queue, void *inValue);

/* 
* Construct an empty queue with size m and initializes number of elements to 0
* See linked_list.c makeList() documentation for method details
* FIELDS:
*       queue: a pointer to a queue struct
*       m: the max size of the queue
*/
void makeQueue(Queue_t *queue, int m);

/* 
* Free the queue
* See linked_list.c FreeList() documentation for method details
* freeQueue also free's the malloc'd queue
* FIELDS:
*       queue: a pointer to a queue struct
*/
void freeQueue(Queue_t *queue);

/* 
* Check if queue is empty 
* is empty when queue->numElem == 0;
* FIELDS:
*       queue: a pointer to a queue struct
*
* RETURN: 1 if empty | 0 if not empty
*/
int qEmpty(Queue_t *queue);

/* 
* Check if queue is full
* is full when queue->numElem == queue->maxSize;
* FIELDS:
*       queue: a pointer to a queue struct
*
* RETURN: 1 if full | 0 if not full
*/
int qFull(Queue_t *queue);
