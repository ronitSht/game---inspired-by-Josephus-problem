#include "person.h"
#include "utils.h"
#include "sorting.h"
#include "game.h"

/*int main() {
	Person* head = InitTheHungerGame();
	PrintCircle(head);
	InsertLaters(head);
	PrintCircle(head);
	head = RemoveCowards(head);
	PrintCircle(head);
	head = SortCircleByName(head);
	PrintCircle(head);
	head = SortCircleByID(head);
	PrintCircle(head);
	LetTheHungerGameBegin(head);
	return 0;
}*/

#include "person.h"
#include "utils.h"
#include "sorting.h"
#include "game.h"

#include <stdio.h>

Person *head, *head_1, *head_2;

void f1() {
	head = InitTheHungerGame();
	PrintCircle(head);
	LetTheHungerGameBegin(head);
}

void f2() {
	head = InitTheHungerGame();
	PrintCircle(head);
	head = SortCircleByName(head);
	PrintCircle(head);
	head = SortCircleByID(head);
	PrintCircle(head);
	LetTheHungerGameBegin(head);
}

void f3() {
	head = InitTheHungerGame();
	PrintCircle(head);
	InsertLaters(head);
	PrintCircle(head);
	head = RemoveCowards(head);
	PrintCircle(head);
	LetTheHungerGameBegin(head);
}

void f45() {
	head = InitTheHungerGame();
	PrintCircle(head);
	InsertLaters(head);
	PrintCircle(head);
	head = RemoveCowards(head);
	PrintCircle(head);
	head = SortCircleByName(head);
	PrintCircle(head);
	head = SortCircleByID(head);
	PrintCircle(head);
	LetTheHungerGameBegin(head);
}

void f6() {
	head_1 = InitTheHungerGame();
	head_2 = InitTheHungerGame();
	PrintCircle(head_1);
	PrintCircle(head_2);
	LetTheHungerGameBegin(head_1);
	LetTheHungerGameBegin(head_2);
}

//main function
int main() {
	int x;
	scanf("%d", &x);
	if (x == 1) {
		f1();
	}
	else if (x == 2) {
		f2();
	}
	else if (x == 3) {
		f3();
	}
	else if (x == 4 || x == 5) {
		f45();
	}
	else if (x == 6) {
		f6();
	}
	else {
		printf("error\n");
	}
	return 0;
}