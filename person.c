

#include <stdio.h>
#include "person.h"
#include "utils.h"
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

#define NAME "Name: "
#define ID "ID: "
#define NUM_OF_KID "Kid #%d: %s\n"
#define KID_NAME "Kid #%d name:\n"
#define NUM_OF_KIDS "Num of kids:\n"

/*
functions declarations
*/
void Print(Person* this);
void CreateNext(Person* this, int isNextNext, ...);
void KillNext(struct Person* this);
struct Person* SelfDestruct(struct Person* this);

/********************************************************************************************************************
* Function Name: Print
* Input: Person* this
* Output: no output
* Function Operation: the function prints the name, the ID and the kids' names
*******************************************************************************************************************/
void Print(Person* this) {
	int i;
	printf(NAME "%s\n", this->name);
	printf(ID "%d\n", this->id);
	if (this->numOfKids != 0) {
		for (i = 0; i < this->numOfKids; i++) {
			printf(NUM_OF_KID, i + 1, this->kids[i]);
		}
	}
}

/********************************************************************************************************************
* Function Name: InitPersonValues
* Input: Person* this
* Output: no output
* Function Operation: the function initializes the name, the ID, the number of kids, the kids and the functions
*                     in the struct Person
*******************************************************************************************************************/
void InitPersonValues(Person* person) {
	char* name = { 0 };
	int id = -1;
	int numOfKids = -1;
	char** kids = { 0 };
	person->next = NULL;
	person->Print = Print;
	person->KillNext = KillNext;
	person->SelfDestruct = SelfDestruct;
	person->CreateNext = CreateNext;
}

/********************************************************************************************************************
* Function Name: CreatePerson
* Input: no input
* Output: Person* person, NULL if the memory allocation failed
* Function Operation: the function initializes the name, the ID, the number of kids, the kids and the functions
*                     in the struct Person, and returns Person* person
*                     if the memory allocation failed, it frees the previos memory allocations of the person
*                     and returns NULL.
*******************************************************************************************************************/
Person* CreatePerson() {
	Person* person;
	char name[80] = { 0 };
	int id;
	int numOfKids;
	char** kids;
	char dummy;
	//a memory allocation for the struct Person
	person = (Person*)malloc(sizeof(Person));

	/*
	if the memory allocation failed, it returns NULL
	*/
	if (person == NULL) {
		return NULL;
	}
	//the function that initializes the fields in the struct
	InitPersonValues(person);
	//the user enters his name
	printf(NAME "\n");
	scanf("%s", name);
	scanf("%c", &dummy);
	//the length of the name
	int length = strlen(name) + 1;
	name[length - 1] = '\0';
	char *personName = (char*)malloc(length * sizeof(char));

	/*
	if the memory allocation failed, it frees the struct
	*/
	if (personName == NULL) {
		free(person);
		return NULL;
	}
	//pass the name that the user entered into the dinamic array
	strcpy(personName, name);
	person->name = personName;
	//the user enters his ID number
	printf(ID "\n");
	scanf("%d", &id);
	//in case that the user entered a negative id number, it will be refered as a positive a number
	if (id < 0) {
		id == (-1)*id;
	}
	person->id = id;
	//the user enters his number of kids
	printf(NUM_OF_KIDS);
	scanf("%d", &numOfKids);
	person->kids = NULL;
	person->numOfKids = numOfKids;

	/*
	if the person has kids (so his number of kids is not equal to 0), we allocate place for the kids
	*/
	if (person->numOfKids != 0) {
		char **kids = (char**)malloc(numOfKids * sizeof(char*));

		/*
		if the memory allocation failed, we free the previous memory allocations of the person,
		and the function returns NULL
		*/
		if (kids == NULL) {
			free(personName);
			free(person);
			return NULL;
		}

		/*
		a loop that enters the names of the kids
		*/
		int i, j;
		for (i = 0; i < numOfKids; i++) {
			printf(KID_NAME, i + 1);
			scanf("%s", name);
			scanf("%c", &dummy);
			//length of the name
			int length = strlen(name) + 1;
			char *kidName = (char*)malloc(length * sizeof(char));

			/*
			if the memory allocation failed, we free the previous memory allocations of the person,
			and the function returns NULL
			*/
			if (kidName == NULL) {
				for (j = 0; j < i; j++) {
					free(kids[j]);
				}
				free(kids);
				free(personName);
				free(person);
				return NULL;
			}
			//pass the name of the kid into the struct
			strcpy(kidName, name);
			kids[i] = kidName;
		}
		person->kids = kids;
	}
	return person;
}

/********************************************************************************************************************
* Function Name: CreateNext
* Input: Person* this, int isNextNext (0/1), and can have another input (Person* this->next) - in this case
*        isNextNext will be 1, and if it does not have another input isNextNext will be 0
* Output: no output
* Function Operation: The function gets the details from the function CreatePerson. In case we want to add a person
*                     in the middle of the linked list (the laters), we use this function while isNextNext is
*                     equal to 1.
*******************************************************************************************************************/
void CreateNext(Person* this, int isNextNext, ...) {
	//the first person to be entered
	Person* newPerson = CreatePerson();

	/*
	if isNextNext = 1, there will be another input in the function (this->next), so we will be able to enter the 
	new person (the later) near his friend (it can be in the middle of the linked list), so here we use the
	variadic function that makes it possible.
	if isNextNext = 0 (else), the new person will be added in the end of the linked list
	*/
	if (isNextNext == 1) {
		va_list ap;
		va_start(ap, isNextNext);
		va_arg(ap, Person*);
		
		//to keep the link to the next person that was before and add the new person to his place in the linked list
		newPerson->next = this->next;
		this->next = newPerson;
		va_end(ap);
	}
	else {
		this->next = newPerson;
	}
}

/********************************************************************************************************************
* Function Name: KillNext
* Input: struct Person* this
* Output: no output
* Function Operation: The function kills the next person by using the function SelfDestruct
*******************************************************************************************************************/
void KillNext(struct Person* this) {
	this->next = SelfDestruct(this->next);
}

/********************************************************************************************************************
* Function Name: SelfDestruct
* Input: struct Person* this
* Output: struct Person*
* Function Operation: The function kills and frees the fields of the person
*******************************************************************************************************************/
struct Person* SelfDestruct(struct Person* this) {
	//for keeping the address of the next person
	Person* nextPointer = this->next;
	free(this->name);
	int i;

	/*
	a loop that frees the kids
	*/
	if (this->kids != NULL) {
		for (i = 0; i < this->numOfKids; i++) {
			free(this->kids[i]);
		}
		free(this->kids);
	}
	//free the person
	free(this);
	return nextPointer;
}