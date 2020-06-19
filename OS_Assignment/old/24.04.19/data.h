/*
* Author: Adam Camer-Pesci
*
* Written: 24/04/2019
*/

/*
* Get two tasks from task_file at a time and put them into the queue
* Calls taskFunc to write to simulation_log
*
* FIELDS: 
*       queue: A pointer to a Queue_t struct
*       numTasks: a pointer to the number of total tasks currently in the queue
*/
void task(Queue_t *queue, char *taskFile);

/*
* Write the current task and arrival time to the simulation_log in the specified format
* FIELDS: 
*       newTask: a Task_t struct -> contains vars for task#, burstTime, arrivalTime
*/
void taskFunc(Task_t *newTask);

/*
* Function called when all tasks in task_file have been placed into the ready queue
* FIELDS: 
*/
void taskcomplete();

/*
* Simulates operations of CPU. 
* Function is called when there is at least one task in the ready queue.
* The task is taken from the ready queue and execution is simulated by a wait()/sleep()
* which lasts from as long as the CPU burst
* FIELDS: 
*/
void cpu(Queue_t *queue);

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a task from the ready queue
*
* FIELDS:     
        task: a pointer toa Task_t struct
*/
void cpuFuncA(Task_t *task);


/*
* Write the current cpu statistics to the sim_log in the specified 
* format when a cpu takes a completes a task
*
* FIELDS:
*       task: a pointer to a Task_t struct     
*/
void cpuFuncB(Task_t *task);

/*
* Write the current cpu statistics to the sim_log in the specified 
* format when there are no more tasks available to be processed
*
* FIELDS:     
*/
void cpuComplete();

/*
* Write the final appendment to the sim_log in the specified format
*
* FIELDS:     
*/
void schedulerComplete();

/*
* Get the current system time
*
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