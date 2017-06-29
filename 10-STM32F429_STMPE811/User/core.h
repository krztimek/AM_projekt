#ifndef _CORE_H_
#define _CORE_H_

#include "data.h"
#include "global_data.h"
#include "rand.h"
#include "menu.h"

void CORE_EnterCriticalSection(void);

void CORE_ExitCriticalSection(void);

/*
Funkcja StringToPoint - zamiana karry na przypisana do niej ilosc punkt�w
*/
int string_to_point(int index);

/*
play_cards - Funkcja w kt�rej okreslona jest cala funkcjonalnosc gry
*/
void play_cards(TypeMoney* moneyToSpend, TypeMoney* moneyToBet);

/*
Samodzielna gra dealera
*/
bool dealer_play(void);

/*
Funkcja wypisujaca komunikat po wejsciu w "Resign"
*/
void exit_game(void);

#endif // _CORE_H_
