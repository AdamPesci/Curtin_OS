#pragma once
/*
* Author: Adam Camer-Pesci
*
* Written: 24/04/2019
*/
void begin(int qSize, char *taskFile);

/*
* Get two tasks from task_file at a time and put them into the queue
* Calls taskFunc to write to simulation_log
*
* FIELDS: 
*       taskFile: A pointer to the task_file
*/
void *task(void *arg);

/*
* Write the current task and arrival time to the simulation_log in the specified format
* FIELDS: 
*       newTask: a Task_t struct -> contains vars for task#, burstTime, arrivalTime
*/
void taskFunc(Task_t *newTask);

/*
* Function called when all tasks in task_file have been placed into the ready queue
* FIELDS: 
        count: an integer value of all the tasks which have been added to the queue
        (but not necessarily completed)
*/
void taskcomplete();

/*
* Simulates operations of CPU. 
* Function is called when there is at least one task in the ready queue.
* The task is taken from the ready queue and execution is simulated by a wait()/sleep()
* which lasts from as long as the CPU burst
*/
void *cpu(void *arg);

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a task from the ready queue
*
* FIELDS:     
*       task: a pointer toa Task_t struct
*       cpuNum: integer ID of cpu number
*/
void cpuFuncA(Task_t *task, int cpuNum);

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a completes a task
*
* FIELDS:
*       task: a pointer to a Task_t struct     
*       cpuNum: integer ID of cpu number
*/
void cpuFuncB(Task_t *task, int cpuNum);

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when there are no more tasks available to be processed 
* FIELDS: 
*       timeString: an array of size 9 to hold current system time
*/
void cpuComplete(int cpuNum, int localNumTasks);

/*
* Write the final appendment to the sim_log in the specified format
* once all tasks have been completed
*/
void schedulerComplete();

/*
* Get the current system time
* FIELDS: 
*       timeString: an array of size 9 to hold current system time      
*/
void getTime(char *timeString);

/*
* Calculate the completion time of a task
*
* FIELDS: 
*       task: a pointer to a task struct        
*/
void calcCompTime(Task_t *task);

/*
* Calculates the difference between two time strings
*
* FIELDS: 
*       t1: a pointer to a string in the format HH:MM:SS
*       t2: a pointer to a string in the format HH:MM:SS       
*/
int minusTime(char *ts1, char *ts2);