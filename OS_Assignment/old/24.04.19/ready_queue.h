/* 
 * Author: Adam Camer-Pesci
 * 
 * Written: 22/04/2019
 */

/*
*TYPEDEF:Struct Queue
*FIELDS: maxSize: The maximum size of the queue 
         numElem: The current number of elements in the list
         list: A linked list
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
         arrivalTime: an array to hold the string representation of current time (See getTime Method)
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
* See linked_list.c documentation for method details
*/
Data_t peek(Queue_t *queue);

/* 
* Remove first item from linked list
* See linked_list.c documentation for method details
*/
void dequeue(Queue_t *queue);

/* 
* Add new item to end of the list
* See linked_list.c documentation for method details
*/
void enqueue(Queue_t *queue, void *inValue);

/* 
* Construct an empty queue with size m and initializes number of elements to 0
* See linked_list.c makeList() documentation for method details
*/
void makeQueue(Queue_t *queue, int m);

/* 
* Free the queue
* See linked_list.c FreeList() documentation for method details
* freeQueue also free's the malloc'd queue
*/
void freeQueue(Queue_t *queue);

/* 
* Check if queue is empty 
* is empty when queue->numElem == 0;
* returns 0 if empty 1 if not empty
*/
int qEmpty(Queue_t *queue);
