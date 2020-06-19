/* driver.c
*
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
      Main method of program, calls begin() to start simulation

  @param argc -> An integer number representing number of command line arguments
  @param argv[] -> An array of input commands (filename containing drawing instructions)
*/
int main(int argc, char *argv[])
{
    /* check command line arguments */
    if (argc < 3 || argc > 3)
    {
        printf("Please try again.\n"
               "To start enter the following: 'scheduler task_file m'\n"
               "(where m is an integer between 1-100)\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* start simulation */
        printf("Simulation starting, please wait.\n");
        int qSize = atoi(argv[2]);
        begin(qSize, argv[1]);
        printf("Simulation complete.\n");
        exit(EXIT_SUCCESS);
    }
    return 0;
} /* END OF PROGRAM */
