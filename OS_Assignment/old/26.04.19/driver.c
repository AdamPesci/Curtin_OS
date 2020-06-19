/*
 * This file contains the main method of the program
 *
 * Author: Adam Camer-Pesci
 * Written 22/04/2019
 */
#include <stdio.h>
#include <stdlib.h>
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
        int qSize = atoi(argv[2]);
        begin(qSize, argv[1]);
        exit(EXIT_SUCCESS);
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