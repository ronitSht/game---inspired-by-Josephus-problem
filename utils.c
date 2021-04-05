

#include <stdio.h>
#include "game.h"
#include <string.h>
#include "person.h"
#include "utils.h"
#define SEPARETING_LINE "----------\n"

/********************************************************************************************************************
* Function Name: PrintCircle
* Input: Person* head
* Output: no output
* Function Operation: the function prints the circle - the name, the ID and the kids' of each one
*******************************************************************************************************************/
void PrintCircle(Person* head) {
	Person* thisPerson;
	thisPerson = head;

	/*
	if there are no people at all, the function prints nothing
	*/
	if (head == NULL) {
		return;
	}

	/*
	when there are people in the circle (not null), the function prints the name, ID and kids' names with
	separting lines between each person and his details
	*/
	printf(SEPARETING_LINE);
	do{
		thisPerson->Print(thisPerson);
		printf(SEPARETING_LINE);
		thisPerson = thisPerson->next;
	} while (thisPerson != NULL);
}

/********************************************************************************************************************
* Function Name: CountPeople
* Input: Person* head, int counter
* Output: int counter
* Function Operation: the function counts how many people there are in the linked list, and returns it
*******************************************************************************************************************/
int CountPeople(Person* head, int counter) {
	Person* thisPerson = head;
	counter = 0;

	/*
	only when there are no people in the linked list, counter is equal to 0
	*/
	if (head == NULL) {
		counter = 0;
		return 0;
	}

	/*
	each time a name is entered into the linked list, the counter grows up
	*/
	while (thisPerson != NULL) {
		counter++;
		thisPerson = thisPerson -> next;
	}
	return counter;
}

/********************************************************************************************************************
* Function Name: FreeMemory
* Input: Person* head
* Output: no output
* Function Operation: the function frees the memory allocations before the person that his allocation failed
*******************************************************************************************************************/
void FreeMemory(Person* head) {
	Person* thisPerson = head;
	while (thisPerson != NULL) {
		thisPerson = thisPerson->SelfDestruct(thisPerson);
	}
}

