This directory contains a Makefile that will compile the program 'scheduler' and the program 'scheduler_debug'.
---------------------------------------------------------------------------------------------------------------------------------------------------------------

All source files are located within the 'src' directory. 
All resources required by the user at run time are located within the 'resources' directory.
All previous iterations of the source code are located withing the 'old' directory.

---------------------------------------------------------------------------------------------------------------------------------------------------------------

I have also included a script to generate a task file for testing purposes.
To generate a task_file simply run generateTF as follows: 
"./generateTF m n" 

- m is the maximum cpu burst time
- n is the number of tasks to be generated

---------------------------------------------------------------------------------------------------------------------------------------------------------------

scheduler is the program which follows the specifications of the assignment outline.
scheduler_debug is a copy of scheduler, however it is compiled using data_debug.c so some output is displayed to the terminal.
This is intended for debugging purposes as it shows the current progress of the simulation in real time.

---------------------------------------------------------------------------------------------------------------------------------------------------------------

To compile both programs simply type "make" from the directory that contains the make file and both programs will be compiled and stored in the 'dist' folder. 
Any required resources from the 'resources' file will be also copied to 'dist'.
Make will move all .o to the 'build' directory and all content required by the user will be placed in 'dist'. 

---------------------------------------------------------------------------------------------------------------------------------------------------------------
** this is done from inside the 'dist' directory *

To run 'scheduler' type: "./scheduler task_file m".
Note: "m" is the maximum size of the ready queue.
EG: "./scheduler task_file 10" will run the simulation with a maximum queue size of 10.

To run 'scheduler_debug' type: "./scheduler_debug task_file m".
The same execution rules as scheduler apply.

---------------------------------------------------------------------------------------------------------------------------------------------------------------

During the simulation, simulation_log will be written in the directory of execution. 

A completion message will be given through the terminal when the simulation has completed. 


Author: Adam Camer-Pesci
