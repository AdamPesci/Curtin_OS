/*
 * This linked list was previously submitted for curtin colleges 2018 Sem2 UCP assignment
 * 
 * Author: Adam Camer-Pesci
 * 
 * Written: 29/10/2018
 */

/*
*TYPEDEF:Struct Data 
*FIELDS: Command: A char pointer a command (string) -> draw/move/rotate etc...
         label: A char pointer to label (string) -> what the command actually must do
*/
typedef struct Data
{
    void *data;
} Data_t;

/*
*TYPEDEF:Struct Node 
*FIELDS: Value: A Data_t value that stores drawing instruction information
         Node: pointers to the next and previous nodes
*/
typedef struct Node
{
    Data_t value;
    struct Node *next;
    struct Node *prev;
} Node_t;

/*
*TYPEDEF:Struct LinkedList
*FIELDS: Node_t: Node pointers to the head and tail nodes
*/
typedef struct LinkedList
{
    Node_t *head;
    Node_t *tail;
} LinkedList_t;

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Sets the head and tail nodes of the linked list == NULL
*EXPORTS: Nothing
*/
void makeList(LinkedList_t *linkedList);

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Checks if the list is empty (if head is == NULL the list must be empty)
*EXPORTS: Returns 0 if empty otherwise returns 1 if there are items in list
*/
int isEmpty(LinkedList_t *linkedList);

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
          void *inValue (a void pointer to some data)
*PROCESS: Creates a new node and stores the value of inValue on the node. This value is inserted as the new head of the list
*EXPORTS: Nothing
*/
void insertFirst(LinkedList_t *linkedList, void *inValue);

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
          void *inValue (a void pointer to some data)
*PROCESS: Creates a new node and stores the value of inValue on the node. This value is inserted as the new tail of the list
*EXPORTS: Nothing
*/
void insertLast(LinkedList_t *linkedList, void *inValue);

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Removes the node stored at the head of the list, updating all required links
*EXPORTS: Nothing
*/
void removeFirst(LinkedList_t *linkedList);

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Removes the node stored at the tail of the list, updating all required links
*EXPORTS: Nothing
*/
void removeLast(LinkedList_t *linkedList);

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
          void (*fptr)(void*) (A pointer to the required print function)
*PROCESS: Iterates through the linked list printing all data stored on that node
*EXPORTS: Nothing
*/
void printList(LinkedList_t *linkedList, void (*fptr)(void *));

/*
*IMPORTS: LinkedList_t *linkedList (A reference to the link list created at the start of the program)
*PROCESS: Iterates through each list node, freeing it as it does, afterward freeing the entire linked list
*EXPORTS: Nothing
*/
void freeList(LinkedList_t *linkedList);

/* 
*IMPORTS: LinkedList_t *linkedList (reference to linked list)
*PROCESS: If head == NULL list must be empy, print error message end exist, otherwise return the value of the head
*EXPORTS: nodeVal (value of the head)
*/
Data_t peekFirst(LinkedList_t *linkedList);

/* 
*IMPORTS: LinkedList_t *linkedList (reference to linked list)
*PROCESS: If head == NULL list must be empy, print error message end exist, otherwise return the value of the tail
*EXPORTS: nodeVal (value of the tail)
*/
Data_t peekLast(LinkedList_t *linkedList);

/* 
*IMPORTS: void *n (A pointer to an integer)
*PROCESS: Prints a integer value 
*EXPORTS: Nothing
*/
void printInt(void *n);

/* 
*IMPORTS: void *f (A pointer to a float)
*PROCESS: Prints a floating point value 
*EXPORTS: Nothing
*/
void printFloat(void *f);