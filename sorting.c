
/******************************************
* Student name: Ronit Shternfeld
* Student ID: 316590512
* Course Exercise Group: 05
* Exercise name: ex6
******************************************/

#include <stdio.h>
#include "sorting.h"
#include "person.h"
#include "utils.h"
#include <malloc.h>
#include <string.h>

/********************************************************************************************************************
* Function Name: SortCircleByID
* Input: Person* head
* Output: Person* head or NULL if there are no people in the game
* Function Operation: the function sorts the people from the smallest ID number to the biggest
*******************************************************************************************************************/
Person* SortCircleByID(Person* head) {
	Person* thisPerson = head;
	Person** structArr = NULL;
	Person* temp = NULL;
	int i, c, d, j;
	int counter = 0;

	/*
	if there are no people (so head is null), it gets out from the function
	*/
	if (head == NULL) {
		return NULL;
	}
	//using the function that counts how many people there are in the linked list
	counter = CountPeople(thisPerson, counter);
	structArr = (Person**)malloc(counter * sizeof(Person*));

	/*
	checking if the memory allocation successed
	*/
	if (structArr == NULL) {
		return NULL;
	}

	/*
	to put the structs of the people in the array
	*/
	for (i = 0; i < counter; i++) {
		structArr[i] = thisPerson;
		thisPerson = thisPerson->next;
	}
	for (c = 0;c < counter - 1;c++) {
		for (d = 0; d < counter - c - 1;d++) {
			/*
			to arrange the array from the smallest ID number to the biggest
			*/
			if ((structArr[d]->id) >(structArr[d + 1]->id)) {
				temp = structArr[d];
				structArr[d] = structArr[d + 1];
				structArr[d + 1] = temp;
			}
		}
	}
	/*
	to enter the arranged struct from the array to the linked list
	*/
	thisPerson = structArr[0];
	Person* headPerson = thisPerson;
	for (j = 1;j < counter;j++) {
		thisPerson->next = structArr[j];
		thisPerson = thisPerson->next;
	}
	thisPerson->next = NULL;
	//freeing the memory allocation
	free(structArr);
	return headPerson;
}

/********************************************************************************************************************
* Function Name: SortCircleByName
* Input: Person* head
* Output: Person* head or NULL if there are no people in the game
* Function Operation: the function sorts the people by the lexicographical order of their names
*******************************************************************************************************************/
Person* SortCircleByName(Person* head) {
	Person* thisPerson = head;
	Person** structArr = NULL;
	Person* temp = NULL;
	int i, c, d, j;
	int counter = 0;

	/*
	if there are no people (so head is null), it gets out from the function
	*/
	if (head == NULL) {
		return NULL;
	}
	//using the function that counts how many people there are in the linked list
	counter = CountPeople(thisPerson, counter);
	structArr = (Person**)malloc(counter * sizeof(Person*));

	/*
	if there are no people (so head is null), it gets out from the function
	*/
	if (structArr == NULL) {
		return NULL;
	}

	/*
	to put the structs of the people in the array
	*/
	for (i = 0; i < counter; i++) {
		structArr[i] = thisPerson;
		thisPerson = thisPerson->next;
	}
	for (c = 0;c < counter - 1;c++) {
		for (d = 0; d < counter - c - 1;d++) {
			/*
			to arrange the array in lexicographical order according to the names
			*/
			if (strcmp(structArr[d]->name, structArr[d + 1]->name)>0) {
				temp = structArr[d];
				structArr[d] = structArr[d + 1];
				structArr[d + 1] = temp;
			}
		}
	}
	/*
	to enter the arranged struct from the array to the linked list
	*/
	thisPerson = structArr[0];
	Person* headPerson = thisPerson;
	for (j = 1;j < counter;j++) {
		thisPerson->next = structArr[j];
		thisPerson = thisPerson->next;
	}
	thisPerson->next = NULL;
	//freeing the memory allocation
	free(structArr);
	return headPerson;
}
