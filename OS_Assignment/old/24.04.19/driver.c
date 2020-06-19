/*
 * This file contains the main method of the program
 *
 * Author: Adam Camer-Pesci
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "linked_list.h"
#include "ready_queue.h"
#include "data.h"
/*
* Desc: 
      Main method of program

  @param argc -> An integer number representing number of command line arguments
  @param argv[] -> An array of input commands (filename containing drawing instructions)
*/
int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 3)
    {
        printf("Please try again.\n"
               "To start enter the following: 'scheduler task_file m'\n"
               "(where m is an integer between 1-100)\n");
        exit(EXIT_FAILURE);
    }
    else
    {

        int qSize = atoi(argv[2]); //length of queue
        
        Queue_t *queue = (Queue_t *)malloc(sizeof(Queue_t));
        makeQueue(queue, qSize);
        printf("%d,%d\n",queue->numElem,queue->maxSize);
        task(queue, argv[1]); //1 thread will run this
        while (!(qEmpty(queue) == 0)) //while the queue is not empty 
        {
            printf("%d,%d\n",queue->numElem,queue->maxSize);
            cpu(queue); //three threads will run this (only one thread can actually do this at a time though)
        }
        freeQueue(queue);
    }
    return 0;
} /*END OF PROGRAM*


    how to get the struct from the queue
    Data_t ret = peek(queue);
    Task_t *stuff = (Task_t *)ret.data;
    
        Data_t stuff = peek(queue);
        Task_t *ret = (Task_t *)stuff.data;
        for (int i = 0; i < queue->maxSize; i++)
        {
            printf("task no: %d burst time: %d arrival time %s\n", ret->taskNum, ret->burstTime,ret->arrivalTime);
            dequeue(queue);
            stuff = peek(queue);
            ret = (Task_t *)stuff.data;
        }
    */