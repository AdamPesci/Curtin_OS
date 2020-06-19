/*
* This File contrains the main functions task() and cpu() needed for this assignment.
* File I/O methods and any methods associated with the afformentioned methods are also inclduded.
* 
* Author: Adam Camer-Pesci
*
* Written: 24/04/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"
#include "ready_queue.h"
#include "data.h"

/*
* Get two tasks from task_file at a time and put them into the queue
* Calls taskFunc to write to simulation_log
*
* FIELDS: 
*       queue: A pointer to a Queue_t struct
*       numTasks: a pointer to the number of total tasks currently in the queue
*/
void task(Queue_t *queue, char *taskFile)
{
    /* Initialize variables */
    int counter = 0;
    FILE *read;
    char buffer[32];
    /*open file in read mode, error check*/
    read = fopen(taskFile, "r");
    if (read == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /* loop through all lines, grabbing one at a time */
        while (fgets(buffer, 32, read) != NULL)
        {
            Task_t *newTask1 = (Task_t *)malloc(sizeof(Task_t));
            Task_t *newTask2 = (Task_t *)malloc(sizeof(Task_t));
            /* scan contents of line into Task_t struct 1 */
            sscanf(buffer, "%d %d", &newTask1->taskNum, &newTask1->burstTime);
            /* get the next line */
            fgets(buffer, 32, read);
            /* scan contents of line into Task_t struct 1 */
            sscanf(buffer, "%d %d", &newTask2->taskNum, &newTask2->burstTime);

            /* if there is room in the queue add it to the queue */
            if (queue->numElem < queue->maxSize - 1)
            {
                /* adding items to queue */
                enqueue(queue, newTask1);
                enqueue(queue, newTask2);
                /* writing to sim_log */
                taskFunc(newTask1);
                taskFunc(newTask2);
                counter = counter + 2;
            }
            /* if there wasn't enough room, wait until there is */
            else
            {
                free(newTask1);
                free(newTask2);
            }
        }
        taskcomplete(counter);
    }
    /* close the file */
    fclose(read);
}

/*
* Write the current task and arrival time to the simulation_log in the specified format
* FIELDS: 
*       newTask: a Task_t struct -> contains vars for task#, burstTime, arrivalTime
*/
void taskFunc(Task_t *newTask)
{
    /* create char array to hold time string 
     - size 9 so there is space for "HH:MM:SS\0"
    */
    getTime(newTask->arrivalTime);

    /* open the file in append mode, error check */
    FILE *write;
    write = fopen("simulation_log", "a");

    if (write == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /* write the the sim_log */
        fprintf(write, "task_%d: %d\nArrival time: %s\n"
                       "-------------------\n",
                newTask->taskNum, newTask->burstTime, newTask->arrivalTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Function called when all tasks in task_file have been placed into the ready queue
* FIELDS: 
*/
void taskcomplete(int counter)
{
    char finTime[9];
    getTime(finTime);

    /* open the file in append mode, error check */
    FILE *write;
    write = fopen("simulation_log", "a");

    if (write == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /* write the the sim_log */
        fprintf(write, "Number of tasks put into Ready-Queue: %d\n"
                       "Terminate at time: %s\n"
                       "-------------------\n",
                counter, finTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Simulates operations of CPU. 
* Function is called when there is at least one task in the ready queue.
* The task is taken from the ready queue and execution is simulated by a wait()/sleep()
* which lasts from as long as the CPU burst
*
* FIELDS:
*       queue: a pointer to a Queue_t struct 
*/
int num_tasks = 0;
int total_waiting_time = 0;
int total_turnaround_time = 0;
void cpu(Queue_t *queue)
{
    /*get a task from the queue */
    Data_t ret = peek(queue);
    Task_t *cast = (Task_t *)ret.data;

    /* copy memory to a new location */
    /*
    this is done because if another cpu is running at the same time
    and it calls peek() before the first cpu has dequeued it there will
    be repeat information and probably some weird errors 
    */
    Task_t *task = (Task_t *)malloc(sizeof(Task_t));
    memcpy(task, cast, sizeof(Task_t));
    /* Cequeue the task so other cpu's can access the queue */
    dequeue(queue);

    /* Call cpuFuncA to write to sim_log */
    cpuFuncA(task);

    /* Sleep for burst time period */
    sleep(task->burstTime);

    /* Call cpuFuncB to write to sim_log */
    cpuFuncB(task);
    //add to numtask variable

    /* calculate waiting time and add to total waiting time */
    minusTime(task->serviceTime, task->arrivalTime);

    /* Calculate turn around time and add to total turn around time */
    minusTime(task->completionTime, task->arrivalTime);

    /* free the task the cpu was using */
    free(task);
    cpuComplete(queue);
}

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a task from the ready queue
*
* FIELDS:     
        task: a pointer toa Task_t struct
*/
void cpuFuncA(Task_t *task)
{
    FILE *write;
    write = fopen("simulation_log", "a");

    if (write == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /* get the service time */
        getTime(task->serviceTime);
        /* write the the sim_log */
        fprintf(write, "Statistics for CPU: \n"
                       "task_%d: %d\n"
                       "Arrival time: %s\n"
                       "Service time: %s\n"
                       "-------------------\n",
                task->taskNum, task->burstTime, task->arrivalTime, task->serviceTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a completes a task
*
* FIELDS:
*       task: a pointer to a Task_t struct     
*/
void cpuFuncB(Task_t *task)
{
    FILE *write;
    write = fopen("simulation_log", "a");

    if (write == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        calcCompTime(task);
        /* write the the sim_log */
        fprintf(write, "Statistics for CPU: \n"
                       "task_%d: %d\n"
                       "Arrival time: %s\n"
                       "Completion time: %s\n"
                       "-------------------\n",
                task->taskNum, task->burstTime, task->arrivalTime, task->completionTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when there are no more tasks available to be processed
*
* FIELDS:     
*/
void cpuComplete(Queue_t *queue)
{
    //write "CPU-x terminates after servicing y tasks"
    if (qEmpty(queue) == 0)
    {
        FILE *write;
        write = fopen("simulation_log", "a");

        if (write == NULL)
        {
            printf("Error opening file!\n");
        }
        else
        {
            /* write the the sim_log */
            fprintf(write, "CPU-x terminates after servicing y tasks : \n"
                           "-------------------\n");
        }
        /* close the file */
        fclose(write);
    }
}

/*
* Write the final appendment to the sim_log in the specified format
*
* FIELDS:     
*/
void schedulerComplete()
{
    /* WRITE:

        Number of tasks: #of tasks
        Average waiting time: w seconds
        Average turn around time: t seconds



        The Number of tasks is the total tasks serviced by the three CPUs, i.e, the value of
        num_tasks. The Average waiting time, and the Average turn around time are computed by
        dividing total_waiting_time and total_turnaround_time with num_tasks, respectively.

        */
}

/*
* Get the current system time
*
* FIELDS: 
*       timeString: an array of size 9 to hold current system time      
*/
void getTime(char *timeString)
{
    /* setup time structs */
    time_t current_time;
    struct tm *time_info;

    /* Return the current time and put it in *current time if current_time is not NULL.  */
    time(&current_time);

    /* 
    Return the `struct tm' representation
    of *current_time in the local timezone.  
    */
    time_info = localtime(&current_time);

    /* format time */
    strftime(timeString, 9, "%H:%M:%S", time_info);
}

/*
* Calculate the completion time of a task
*
* FIELDS: 
*       task: a pointer to a task struct        
*/
void calcCompTime(Task_t *task)
{
    /* initialize all variables */
    int time1[4];
    int i = 0;
    int tsecs = 0;
    char str[9];
    char *token;

    /* tokenize the serivce time string */
    strcpy(str, task->serviceTime);
    token = strtok(str, ":");
    while (token)
    {
        time1[i] = atoi(token);
        token = strtok(NULL, ":");
        i++;
    }
    /* convert to seconds and add burst time */
    time1[0] = time1[0] * 3600;
    time1[1] = time1[1] * 60;
    for (i = 0; i < 3; i++)
    {
        tsecs = tsecs + time1[i];
    }
    tsecs = tsecs + task->burstTime;

    /* convert back to HH:MM:SS format */
    time1[0] = tsecs / 3600;
    time1[1] = tsecs % 3600 / 60;
    time1[2] = tsecs % 3600 % 60;
    /* save data to completion time var in task struct */
    snprintf(task->completionTime, 9, "%02d:%02d:%02d", time1[0], time1[1], time1[2]);
}

/*
* Calculates the difference between two time strings
*
* FIELDS: 
*       t1: a pointer to a string in the format HH:MM:SS
*       t2: a pointer to a string in the format HH:MM:SS
*         
*/
int minusTime(char *t1, char *t2)
{
    /* initialize all variables */
    int time1[4];
    int time2[4];
    int i = 0;
    int tsecs1 = 0;
    int tsecs2 = 0;
    int ret = 0;
    char str[9];
    char *token;

    /* tokenize the first string */
    strcpy(str, t1);
    token = strtok(str, ":");
    while (token)
    {
        time1[i] = atoi(token);
        token = strtok(NULL, ":");
        i++;
    }
    /* convert HH and MM into seconds */
    time1[0] = tsecs1 * 3600;
    time1[1] = tsecs1 * 60;

    /* tokenize the second string */
    i = 0;
    strcpy(str, t2);
    token = strtok(str, ":");
    while (token)
    {
        time2[i] = atoi(token);
        token = strtok(NULL, ":");
        i++;
    }
    /* convert HH and MM into seconds */
    time2[0] = tsecs2 * 3600;
    time2[1] = tsecs2 * 60;

    /* get total seconds for time1[] and time2[] */
    for (i = 0; i < 3; i++)
    {
        tsecs1 = tsecs1 + time1[i];
        tsecs2 = tsecs2 + time2[i];
    }

    /* return difference in time */
    ret = tsecs1 - tsecs2;
    return ret;
}
/*END*/
