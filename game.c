

#include <stdio.h>
#include "game.h"
#include <malloc.h>
#include <string.h>
#include "person.h"
#include "utils.h"

#define ADD_PERSON "Add a person to the game? (0|1)\n"
#define LATE_PERSON "Are you late? (0|1)\n"
#define INSERT_FRIEND_ID "Insert your best friend's ID:\n"
#define NO_SUCH_ID "No Such ID: %d\n"
#define ARE_YOU_COWARD "Is there a coward in here? (0|1)\n"
#define ID_COWARD "Insert your ID, you, lame pudding-heart coward:\n"
#define WORLD_KNOWS_YOU_COWARD "Let the world know that you are a coward, %s!\n"
#define SOMEONE_KILLS_SOMEONE "%s kills %s "
#define KILLS_KIDS "and %s "
#define VICTORY_ANOUNCEMENT "Ah, ha, ha, ha, stayin' alive, stayin' alive! Ah, ha, ha, ha, \"%s\" stayin' alive!\n"

/********************************************************************************************************************
* Function Name: InitTheHungerGame
* Input: no input
* Output: Person* head or NULL if there are no people in the game or when the memory allocation was failed
* Function Operation: the function initializes the game:
*                     if the user enters 1, he can enter his details: name, ID and his kids' names.
*				      if the user enters 0, he doesn't want to enter a person to the game and it returns NULL.
*                     when the memory allocation was failed it also returns NULL.
*                     if the function LetTheHungerGameBegin will not be called at all after InitTheHungerGame,
*                     there will be a memory leak (which is fine) because the free is done in LetTheHungerGameBegin. 
*******************************************************************************************************************/
Person* InitTheHungerGame() {
	char dummy;
	Person* head = NULL;
	Person* lastOne = NULL;
	int userDigit;
	
	printf(ADD_PERSON);
	scanf("%d", &userDigit);
	scanf("%c", &dummy);
	while (userDigit == 1) {

		/*
		if it's the first person, it gets the details of the person from the function CreatePerson
		if it is not the first person, it gets the details from the function CreateNext
		*/
		if (head == NULL) {
			head = CreatePerson();
			lastOne = head;
		}
		else {
			head->CreateNext(lastOne, 0);
			lastOne = lastOne->next;
		}
		printf(ADD_PERSON);
		scanf("%d", &userDigit);
		scanf("%c", &dummy);
	}
	
	/*
	if the user entered 1 (so a person should be in the struct) and one of those fields are NULL and they
	should'nt be, the memory allocation failed, and we free all the people before the person that the 
	memory failed in it
	*/
	if ((userDigit == 1) && ((head->name == NULL) || ((head->kids == NULL) && (head->numOfKids != 0)))) {
		FreeMemory(head);
	}

	/*
	If the first person is null (so there are no people), the function returns NULL.
	If there it is not empty (so there are at least one person), it returns the head.
	*/
	if (head == NULL) {
		return NULL;
	}
	else {
		return head;
	}	
}

/********************************************************************************************************************
* Function Name: InsertLaters
* Input: no input
* Output: Person* head or NULL if there are no people in the game or when the memory allocation was failed
* Function Operation: the function enters laters to the game near their friends.
*                     if the memory allocation will failed, only the later will be freed in the function CreateNext
*                     that uses the function CreatePerson
*******************************************************************************************************************/
void InsertLaters(Person* head) {
	Person* headPerson = head;
	int userDigit, friendId=0;
	char dummy;
	int counter = 0;

	/*
	if there are no people (so head is null), it gets out from the function
	*/
	if (head == NULL){
		return;
	}
	printf(LATE_PERSON);
	scanf("%d", &userDigit);
	scanf("%c", &dummy);

	/*
	while the user enters the digit 1, the loop of entering the laters runs
	*/
	while (userDigit == 1) {
			printf(INSERT_FRIEND_ID);
			//the user enters his friend's ID number
			scanf("%d", &friendId);
			scanf("%c", &dummy);

			/*
			when the linked list is not empty, the ID number of the friend is searched.
			if it is found, the counter grows up, so it becomes bigger than 0.
			*/
			while (headPerson != NULL) {
				if (headPerson->id == friendId) {
					//to check if there is a person with the ID of the friend
					counter++;
					break;
				}
				headPerson = headPerson->next;
			}
		
		/*
		If there isn't a person with the ID of the friend, counter will remain 0 and the statement will be printed.
		If there is a person with the ID of the friend, the person that was late will be added to linked list after
		the friend.
		*/
		if (counter == 0) {
			printf(NO_SUCH_ID, friendId);
			headPerson = head;
		}
		else {
			headPerson->CreateNext(headPerson, 1, headPerson->next);
			counter = 0;
			headPerson = head;
		}
		//the loop returns again and the user is asked again if he wants to add a later
		printf(LATE_PERSON);
		scanf("%d", &userDigit);
		scanf("%c", &dummy);
	}
}

/********************************************************************************************************************
* Function Name: RemoveCowards
* Input: Person* head
* Output: Person* head or NULL if there are no people in the game or when the memory allocation failed
* Function Operation: the function removes the cowards from the game
*******************************************************************************************************************/
Person* RemoveCowards(Person* head) {
	Person* coward = head;
	Person* beforeCoward = NULL;
	Person* temp = NULL;
	int userDigit, idNumber;
	char dummy;
	int counter = 0;

	/*
	if there are no people (so head is null), it gets out from the function
	*/
	if (head == NULL) {
		return NULL;
	}
	printf(ARE_YOU_COWARD);
	//the user enters a digit
	scanf("%d", &userDigit);
	scanf("%c", &dummy);

	/*
	the loop runs when the digit that the user enters is 1, so there is a coward
	*/
	while (userDigit == 1) {
		printf(ID_COWARD);
		//the user enters his ID number
		scanf("%d", &idNumber);
		scanf("%c", &dummy);

		/*
		the loop runs when the linked list is not empty
		*/
		while (coward != NULL) {
				
			/*
			for finding the person who is coward by his ID. if he is found, the counter grows up,
			so it is not equal to 0
			*/
			if (coward->id == idNumber) {
				counter++;
				break;
			}
			beforeCoward = coward;
			coward = coward->next;
		}

		/*
		if the ID of the coward was found, he is removed from the linked list and does not participate in the game
		if not, there is not such ID sentence is printed
		*/
		if (counter != 0) {
			if (coward != head) {
				//finding the person before the coward
				if (beforeCoward != NULL) {
					beforeCoward->next = coward->next;
				}
			}
			//if the coward is the head of the linked list, this for keeping an head for the list
			else if (coward == head) {
					head=coward->next;
			}
		}
		else {
			printf(NO_SUCH_ID, idNumber);
			coward = head;
			//the loop returns again and the user is asked again if he is a coward
			printf(ARE_YOU_COWARD);
			scanf("%d", &userDigit);
			scanf("%c", &dummy);
			continue;
		}
		//the sentence for the cowards
		printf(WORLD_KNOWS_YOU_COWARD, coward->name);
			
		//to take out the coward from the linked list
		coward->SelfDestruct(coward);
		if (head == NULL) {
			return NULL;
		}
		coward = head;
		counter = 0;
		//the loop returns again and the user is asked again if he is a coward
		printf(ARE_YOU_COWARD);
		scanf("%d", &userDigit);
		scanf("%c", &dummy);
	}
	return head;
}

/********************************************************************************************************************
* Function Name: LetTheHungerGameBegin
* Input: Person* head
* Output: no output
* Function Operation: the function of the game - there is a circle, the first person kills his next person, the
*                     person after the dead person kills his next person, until only one person remains alive, 
*                     and he is the winner of the game.
*                     in the end of the function all the memory that was allocated is being free. 
*******************************************************************************************************************/
void LetTheHungerGameBegin(Person* head) {
	Person* thisPerson = head;
	Person* temp = NULL;
	int i;

	/*
	if there are no people (so head is null), it gets out from the function
	*/
	if (head == NULL) {
		return;
	}
	//for closing the circle
	while (thisPerson->next != NULL) {
		thisPerson = thisPerson->next;
	}
	thisPerson->next = head;

	/*
	a loop that runs through the circle untill it reaches to the last person
	*/
	thisPerson = head;
	while (thisPerson->next != thisPerson) {
		//printing who kills whom and also the children
		printf(SOMEONE_KILLS_SOMEONE, thisPerson->name, thisPerson->next->name);
		if (thisPerson->next->numOfKids != 0) {
			for (i = 0; i < thisPerson->next->numOfKids; i++) {
				printf(KILLS_KIDS, thisPerson->next->kids[i]);
			}
		}
		printf("\n");
		//killing the next person
		thisPerson->KillNext(thisPerson);
		//the person before the person that is being killed gets the address of the person after him.
		thisPerson = thisPerson->next;
	}
	//the victory anouncement
	printf(VICTORY_ANOUNCEMENT, thisPerson->name);
	//freeing the memory
	thisPerson->SelfDestruct(thisPerson);
}