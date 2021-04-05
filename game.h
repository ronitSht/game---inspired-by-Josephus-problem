#ifndef GAME_H
#define GAME_H

#include "person.h"

//general - main - func -createperson, loop createnextperson till I want to stop
Person* InitTheHungerGame();
void InsertLaters(Person* head);
Person* RemoveCowards(Person* head);
void LetTheHungerGameBegin(Person* head);

#endif
