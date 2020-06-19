/* data.c
*
* This File contains the main functions task() and cpu() needed for this assignment.
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
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "linked_list.h"
#include "ready_queue.h"
#include "data.h"

/* Declare and initialize mutex and condition variables */
pthread_mutex_t m_lock = PTHREAD_MUTEX_INITIALIZER; /* Lock used whenever a race condition is encountered */
pthread_cond_t more = PTHREAD_COND_INITIALIZER;     /* Signal used by task to let CPU's know there are tasks in the queue */
pthread_cond_t less = PTHREAD_COND_INITIALIZER;     /* Signal used by CPU's to let task know there is room in the queue */

/* Declare Global variables to be used by all cpu's */
Queue_t *queue;
int num_tasks = 0;
int total_waiting_time = 0;
int total_turnaround_time = 0;
int is_done = 0;

/*
* Starter method for simulation
* Creates all threads and handles a 
*
* FIELDS: 
*       qSize: the size of the queue, given as a command line param
*       taskFile: A pointer to the task_file
*/
void begin(int qSize, char *taskFile)
{
    int cpuNum1 = 1;
    int cpuNum2 = 2;
    int cpuNum3 = 3;

    /* Create queue */
    queue = (Queue_t *)malloc(sizeof(Queue_t));
    makeQueue(queue, qSize);

    /* Create task() thread */
    pthread_t taskThreadID;
    pthread_attr_t taskThreadAttr;
    pthread_attr_init(&taskThreadAttr);
    pthread_create(&taskThreadID, &taskThreadAttr, task, taskFile);

    /* Create CPU_1 thread */
    pthread_t cpu1;
    pthread_attr_t cpu1Attr;
    pthread_attr_init(&cpu1Attr);
    pthread_create(&cpu1, &cpu1Attr, cpu, &cpuNum1);

    /* Create CPU_2 thread */
    pthread_t cpu2;
    pthread_attr_t cpu2Attr;
    pthread_attr_init(&cpu2Attr);
    pthread_create(&cpu2, &cpu1Attr, cpu, &cpuNum2);

    /* Create CPU_3 thread */
    pthread_t cpu3;
    pthread_attr_t cpu3Attr;
    pthread_attr_init(&cpu3Attr);
    pthread_create(&cpu3, &cpu3Attr, cpu, &cpuNum3);

    /* Join all threads once they have finished */
    pthread_join(taskThreadID, NULL);
    pthread_join(cpu1, NULL);
    pthread_join(cpu2, NULL);
    pthread_join(cpu3, NULL);

    /* Write final appendment to simulation_log */
    schedulerComplete();
    freeQueue(queue);

    /* Destroy all mutex and condition variables */
    pthread_cond_destroy(&more);
    pthread_cond_destroy(&less);
    pthread_mutex_destroy(&m_lock);
}

/*
* Gets tasks from the task_file and adds them to the ready queue
* Signals CPU() when there is tasks available for processing
* Calls taskFunc to write to simulation_log
*
* FIELDS: 
*       arg: A pointer to the task_file
*/
void *task(void *arg)
{
    /* Initialize local variables */
    char *taskFile = (char *)arg;
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
            /* if the queue is not empty, wake up all threads waiting on more condition */
            if (qEmpty(queue) != 1)
            {
                pthread_cond_broadcast(&more);
            }

            /* obtain lock, check if queue is full, if so wait*/
            pthread_mutex_lock(&m_lock);
            while (qFull(queue) == 1)
            {
                pthread_cond_wait(&less, &m_lock);
            }
            /* if the queue is not full and there is space for 2 tasks in the queue add them */
            if (qFull(queue) != 1 && queue->numElem < queue->maxSize - 1)
            {
                /* add and queue first task */
                Task_t *newTask1 = (Task_t *)malloc(sizeof(Task_t));
                sscanf(buffer, "%d %d", &newTask1->taskNum, &newTask1->burstTime);
                enqueue(queue, newTask1);
                taskFunc(newTask1);
                /* as long as fgets is not null add the second task (done because if EOF will get repeat last task) */
                if (fgets(buffer, 32, read) != NULL)
                {
                    Task_t *newTask2 = (Task_t *)malloc(sizeof(Task_t));
                    sscanf(buffer, "%d %d", &newTask2->taskNum, &newTask2->burstTime);
                    enqueue(queue, newTask2);
                    taskFunc(newTask2);
                    counter++;
                }
                counter++;
            }
            /* if the queue is not full and there is only space for 1 task add it */
            else if (qFull(queue) != 1 && queue->numElem < queue->maxSize)
            {
                Task_t *newTask1 = (Task_t *)malloc(sizeof(Task_t));
                sscanf(buffer, "%d %d", &newTask1->taskNum, &newTask1->burstTime);
                enqueue(queue, newTask1);
                /* Once added write to sim_log and increment local counter */
                taskFunc(newTask1);
                counter++;
            }
            /* release the lock */
            pthread_mutex_unlock(&m_lock);
        }
        /* once loop exits, all tasks have been added to queue, write end of task appendment */
        pthread_mutex_lock(&m_lock);
        taskcomplete(counter);
        pthread_mutex_unlock(&m_lock);
        /* update control flag, (this doesnt need to be synchronized as no other thread alters the value of is_done) */
        is_done = 1;
    }
    /* close the file and terminate thread */
    fclose(read);
    pthread_exit(NULL);
}

/*
* Simulates operations of CPU. 
* Function is called when there is at least one task in the ready queue.
* The task is taken from the ready queue and execution is simulated by a wait()/sleep()
* which lasts from as long as the CPU burst
*
* FIELDS: 
*       arg: A integer value indicating the CPU number
*/
void *cpu(void *arg)
{
    int cpuNum = *(int *)arg;
    int localNumTasks = 0;

    /* acquire lock and check if queue is empty. If so, block */
    pthread_mutex_lock(&m_lock);
    while (qEmpty(queue) == 1)
    {
        pthread_cond_wait(&more, &m_lock);
    }
    /* release lock */
    pthread_mutex_unlock(&m_lock);
    /* while the queue is not empty, continue to process tasks*/
    while (qEmpty(queue) != 1)
    {
        /* acquire the lock at the start of every iteration */
        pthread_mutex_lock(&m_lock);
        Data_t ret = peek(queue);
        Task_t *cast = (Task_t *)ret.data;
        /* copy memory to a new location */
        /*
        this is done so we can release the queue lock as early as possible 
        */
        Task_t *task = (Task_t *)malloc(sizeof(Task_t));
        memcpy(task, cast, sizeof(Task_t));
        dequeue(queue);
        cpuFuncA(task, cpuNum);
        /* release lock so other threads can do processing */
        pthread_mutex_unlock(&m_lock);
        /* signal task() if there is room for more tasks in the queue */
        if (queue->numElem < queue->maxSize && is_done != 1)
        {
            pthread_cond_signal(&less);
        }
        sleep(task->burstTime);
        localNumTasks++;
        /* acquire lock do appendments to sim_log, update shared thread variables */
        pthread_mutex_lock(&m_lock);
        cpuFuncB(task, cpuNum);
        num_tasks++;
        total_waiting_time = total_waiting_time + minusTime(task->serviceTime, task->arrivalTime);
        total_turnaround_time = total_turnaround_time + minusTime(task->completionTime, task->arrivalTime);
        /* release lock after each iteration */
        pthread_mutex_unlock(&m_lock);
        free(task);
    }
    /* acquire lock when accessing sim_log at completion do appendments and release lock*/
    pthread_mutex_lock(&m_lock);
    cpuComplete(cpuNum, localNumTasks);
    pthread_mutex_unlock(&m_lock);
    pthread_exit(NULL);
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
        fprintf(write, "task_%.2d: %d\nArrival time: %s\n"
                       "-----------------------------------------\n",
                newTask->taskNum, newTask->burstTime, newTask->arrivalTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Function called when all tasks in task_file have been placed into the ready queue
* FIELDS: 
*       count: an integer value of all the tasks which have been added to the queue
*       (but not necessarily completed)
*/
void taskcomplete(int count)
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
                       "-----------------------------------------\n",
                count, finTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a task from the ready queue
*
* FIELDS:     
*       task: a pointer toa Task_t struct
*       cpuNum: the cpu's number (1,2,3...n)
*/
void cpuFuncA(Task_t *task, int cpuNum)
{
    /* open the file */
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
        fprintf(write, "Statistics for CPU_%d: \n"
                       "task_%.2d: %d\n"
                       "Arrival time: %s\n"
                       "Service time: %s\n"
                       "-----------------------------------------\n",
                cpuNum, task->taskNum, task->burstTime, task->arrivalTime, task->serviceTime);
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
*       cpuNum: the cpu's number (1,2,3...n)    
*/
void cpuFuncB(Task_t *task, int cpuNum)
{
    /* open the file */
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
        fprintf(write, "Statistics for CPU_%d: \n"
                       "task_%.2d: %d\n"
                       "Arrival time: %s\n"
                       "Completion time: %s\n"
                       "-----------------------------------------\n",
                cpuNum, task->taskNum, task->burstTime, task->arrivalTime, task->completionTime);
    }
    /* close the file */
    fclose(write);
}

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when there are no more tasks available to be processed
*
* FIELDS:
*       cpuNum: the cpu's number (1,2,3...n)
*       numTasks: the number of tasks the simulated CPU completed
*/
void cpuComplete(int cpuNum, int numTasks)
{
    /* open the file */
    FILE *write;
    write = fopen("simulation_log", "a");

    if (write == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /* write the the sim_log */
        fprintf(write, "CPU_%d terminates after servicing %d tasks\n"
                       "-----------------------------------------\n",
                cpuNum, numTasks);
    }
    /* close the file */
    fclose(write);
}

/*
* Write the final appendment to the sim_log in the specified format
* once all tasks have been completed
*/
void schedulerComplete()
{
    /* open the file */
    FILE *write;
    write = fopen("simulation_log", "a");

    if (write == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /* write the the sim_log */
        fprintf(write, "Number of tasks: %d\n"
                       "Average waiting time: %.2lf seconds\n"
                       "Average turnaround time: %.2lf seconds\n"
                       "-----------------------------------------\n",
                num_tasks, ((double)total_waiting_time / (double)num_tasks),
                (double)total_turnaround_time / (double)num_tasks);
    }
    /* close the file */
    fclose(write);
}

/*
* Get the current system time
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
    time1[0] = time1[0] * 3600;
    time1[1] = time1[1] * 60;

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
    time2[0] = time2[0] * 3600;
    time2[1] = time2[1] * 60;

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
