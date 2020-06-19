/*
 * This file contains the methods used for a linked list struct
 * 
 * This linked list was previously submitted for curtin colleges 2018 Sem2 UCP assignment
 * 
 * Author: Adam Camer-Pesci
 * 
 * Written: 29/10/2018
 */
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Sets the head and tail nodes of the linked list == NULL
*EXPORTS: Nothing
*/
void makeList(LinkedList_t *linkedList)
{

    linkedList->head = NULL;
    linkedList->tail = NULL;
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Checks if the list is empty (if head is == NULL the list must be empty)
*EXPORTS: Returns 0 if empty otherwise returns 1 if there are items in list
*/
int isEmpty(LinkedList_t *linkedList)
{
    int isEmpty = 1;
    if (linkedList->head == NULL)
    {
        isEmpty = 0;
    }
    return isEmpty;
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
          void *inValue (a void pointer to some data)
*PROCESS: Creates a new node and stores the value of inValue on the node. This value is inserted as the new head of the list
*EXPORTS: Nothing
*/
void insertFirst(LinkedList_t *linkedList, void *inValue)
{
    /*
     - Create new node pointer, malloc it to the size of a node struct
     - Set newNodes value = to inValue
     - Initialize next and previous node pointers
    */
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    newNode->value.data = inValue;
    newNode->next = NULL;
    newNode->prev = NULL;
    /*
    - If the list is empty, set the head and tail = to the new node
    */
    if (isEmpty(linkedList) == 0)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    /*
    - If the list is NOT empty
    - Set newNodes previous = to NULL
    - Set newNodes next = to the head of the linked list
    - Set the heads previous node = to newNode
    - Finally, update the head of the node so it is pointing at the new node
    */
    else
    {
        newNode->prev = NULL;
        newNode->next = linkedList->head;
        linkedList->head->prev = newNode;
        linkedList->head = newNode;
    }
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
          void *inValue (a void pointer to some data)
*PROCESS: Creates a new node and stores the value of inValue on the node. This value is inserted as the new tail of the list
*EXPORTS: Nothing
*/
void insertLast(LinkedList_t *linkedList, void *inValue)
{
    /*
    - Create new node pointer, malloc it to the size of a node struct
    - Set newNodes value = to inValue
    - Initialize next and previous node pointers
    */
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    newNode->value.data = inValue;
    newNode->next = NULL;
    newNode->prev = NULL;

    /*
    - If the list is empty, set the head and tail = to the new node
    */
    if (isEmpty(linkedList) == 0)
    {
        linkedList->head = newNode;
        linkedList->tail = newNode;
    }
    /*
    - If the list is NOT empty
    - Set newNodes next = to NULL
    - Set newNodes prev = to the tail of the linked list
    - Set the tails next node = to newNode
    - Finally, update the tail of the node so it is pointing at the new node
    */
    else
    {
        newNode->next = NULL;
        newNode->prev = linkedList->tail;
        linkedList->tail->next = newNode;
        linkedList->tail = newNode;
    }
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Removes the node stored at the head of the list, updating all required links
*EXPORTS: Nothing
*/
void removeFirst(LinkedList_t *linkedList)
{
    /*
    - If the list is empty, print a list is empty message
    */
    if (isEmpty(linkedList) == 0)
    {
        printf("List is empty.\n");
    }
    /*
    - If the list is NOT empty and the head is = to the tail and there is only 1 node in the list so remove it
    - Create a temp pointer, set temp to the head, set head to NULL, free temp
    */
    else if (linkedList->head == linkedList->tail)
    {
        Node_t *temp;
        temp = linkedList->head;
        linkedList->head = NULL;
        free(temp);
    }
    /*
    - If the list is NOT empty and there are multiple items in the list
    - Create a temp pointer
    - Point temp at the head of the linked list
    - Update the head of the list to be pointing at the current heads next node
    - Set the head nodes prev node = to NULL
    - Free the temp node (which is pointing at the current head node)
    */
    else
    {
        Node_t *temp;
        temp = linkedList->head;
        linkedList->head = linkedList->head->next;
        linkedList->head->prev = NULL;
        free(temp);
    }
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Removes the node stored at the tail of the list, updating all required links
*EXPORTS: Nothing
*/
void removeLast(LinkedList_t *linkedList)
{
    /*
    - If the list is empty, print a list is empty message
    */
    if (isEmpty(linkedList) == 0)
    {
        printf("List is empty.\n");
    }
    /*
    - If the list is NOT empty and the head is = to the tail and there is only 1 node in the list so remove it
    - Create a temp pointer, set temp to the head, set head to NULL, free temp
    */
    else if (linkedList->head == linkedList->tail)
    {
        Node_t *temp;
        temp = linkedList->head;
        linkedList->head = NULL;
        free(temp);
    }
    /*
    - If the list is NOT empty and there are multiple items in the list
    - Create a temp pointer
    - Point temp at the tail of the linked list
    - Update the tail of the list to be pointing at the current tails prev node
    - Set the head nodes next node = to NULL
    - Free the temp node (which is pointing at the current head node)
    */
    else
    {
        Node_t *temp;
        temp = linkedList->tail;
        linkedList->tail = linkedList->tail->prev;
        linkedList->tail->next = NULL;
        free(temp);
    }
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Iterates through the linked list printing all data stored on that node
*EXPORTS: Nothing
*/
void printList(LinkedList_t *linkedList, void (*fptr)(void *))
{
    /*
    - If the list is empty, print a list is empty message
    */
    if (isEmpty(linkedList) == 0)
    {
        printf("List is Empty\n");
    }
    /*
    - If the list is NOT empty
    - Create new Node_t pointer
    - Point current to the head of the list
    - While current is not NULL (while there are more links to iterate over)
    - print information
    - Get the next node to continue the loop
    - Once current = null the loop will and so print 'End'
    */
    else
    {
        Node_t *current;
        current = linkedList->head;
        while (current != NULL)
        {
            (*fptr)(current->value.data);
            current = current->next;
        }
        printf("-> End\n");
    }
}

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Iterates through each list node, freeing it as it does, afterward freeing the entire linked list
*EXPORTS: Nothing
*/
void freeList(LinkedList_t *linkedList)
{
    /*
    - Create current and next pointers
    - Set current = to the head of the list
    - While current is not null (while there are more elements in the list)
    - Set next to currents next node
    - Free whatever data is on the node
    - Free the current node
    - Update current to next
    - Once the current = null the loop has ended free the entire list
    */
    Node_t *current, *next;
    current = linkedList->head;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    free(linkedList);
}

/* 
*IMPORTS: LinkedList_t *linkedList (reference to linked list)
*PROCESS: If head == NULL list must be empy, print error message end exist, otherwise return the value of the head
*EXPORTS: nodeVal (value of the head)
*/
Data_t peekFirst(LinkedList_t *linkedList)
{
    /* Create Data_t struct nodeVal (the thing we want to get) */
    Data_t nodeVal;
    /*
    - If the list is empty, print a list is empty message
    */
    if (isEmpty(linkedList) == 0)
    {
        printf("List is Empty\n");
    }
    /*
    - If the list is NOT empty, return the data stored at the head of the list
    */
    else
    {
        nodeVal = linkedList->head->value;
    }
    return nodeVal;
}

/* 
*IMPORTS: LinkedList_t *linkedList (reference to linked list)
*PROCESS: If head == NULL list must be empy, print error message end exist, otherwise return the value of the tail
*EXPORTS: nodeVal (value of the tail)
*/
Data_t peekLast(LinkedList_t *linkedList)
{
    /* Create Data_t struct nodeVal (the thing we want to get) */
    Data_t nodeVal;
    /*
    - If the list is empty, print a list is empty message
    */
    if (isEmpty(linkedList) == 0)
    {
        printf("List is Empty\n");
    }
    /*
    - If the list is NOT empty, return the data stored at the tail of the list
    */
    else
    {
        nodeVal = linkedList->tail->value;
    }
    return nodeVal;
}

/* 
*IMPORTS: void *n (A pointer to an integer)
*PROCESS: Prints a integer value 
*EXPORTS: Nothing
*/
void printInt(void *n)
{
    printf("%d ", *(int *)n);
}

/* 
*IMPORTS: void *f (A pointer to a float)
*PROCESS: Prints a floating point value 
*EXPORTS: Nothing
*/
void printFloat(void *f)
{
    printf("%f ", *(float *)f);
}
