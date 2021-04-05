

#ifndef UTILS_H
#define UTILS_H

#include "person.h"

/********************************************************************************************************************
* Function Name: PrintCircle
* Input: Person* head
* Output: no output
* Function Operation: the function prints the circle - the name, the ID and the kids' of each one
*******************************************************************************************************************/
void PrintCircle(Person* head);

//more functions declarations

/********************************************************************************************************************
* Function Name: CountPeople
* Input: Person* head, int counter
* Output: int counter
* Function Operation: the function counts how many people there are in the linked list, and returns it
*******************************************************************************************************************/
int CountPeople(Person* head, int counter);

/********************************************************************************************************************
* Function Name: FreeMemory
* Input: Person* head
* Output: no output
* Function Operation: the function frees the memory allocations before the person that his allocation failed
*******************************************************************************************************************/
void FreeMemory(Person* head);

#endif

