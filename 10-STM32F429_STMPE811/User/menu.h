#ifndef __menu_h
#define __menu_h

#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_stmpe811.h"
#include <stdbool.h>
#include <stdio.h>
#include "cards.h"
#include "core.h"

typedef struct {
	int value;
	char type[10];
	bool ifbudget;
} TypeMoney;


typedef struct {
char name[16];
uint8_t start_index;
bool ifdealer;
uint8_t points;
} Player;

typedef struct {
uint8_t x;
uint16_t y;
uint8_t length;
uint8_t width;
char text[10];
} Rectangle;

/*
Funkcja Cards_Randomize - tasowanie kart
*/
uint8_t rand_function(void);
void cards_randomize(void);

/*
Funkcja StringToPoint - zamiana karry na przypisana do niej ilosc punktï¿½w
*/
int StringToPoint(int index);

/*
ShowCards - Funkcja wypisujaca na ekran karty i ilosc punktï¿½w danego uzytkownika
Player P - zawodnik lub dealer
iterator - ilosc kart, ktï¿½re nalezy wypisac
*/
void ShowCards(Player* P, int iterator);
/*
PlayCards - Funkcja w ktï¿½rej okreslona jest cala funkcjonalnosc gry
*/
void PlayCards(TypeMoney* moneyToSpend, TypeMoney* moneyToBet);

/*
Draw_Rectangle - Funkcja rysujaca prostokat o okreslonym ksztalcie
*/
void Draw_Rectangle(Rectangle rect, TM_FontDef_t *font, uint32_t color);

/*
LCDInitialization - Inicjalizacja wyswietlacza LCD
*/
void LCDInitialization(void);

/*
Funkcja wypisujaca na ekran struktury A1, B1 i C1, pokazuje na ekranie okreslone napisy
i przyciski w etapie wyboru wartosci budgetu i betu
*/
void print_choose(void);

/*
Funkcja posiadajaca mechanizm umozliwiajacy zmiany wartosci struktury TypeMoney podanej przez wskaznik (budget i bet)
*/
void change_money(TypeMoney* Money);

/*
Funkcja wypisujaca glówne menu gry (new game, change bet i resign)
*/
void show_menu(void);

/*
Funkcja pozwalajaca za pomoca odpowiedniej zmiennej wejsc w dany etap menu. 
*/
void change_menu(void);

/*
Funkcja wypisujaca komunikat po wejsciu w "Resign"
*/
void exit_game(void);

/*
Funkcja pozwalajaca odczytac dane z orzycisnietych elementów w czasie gry i wybór zmian w kartach spowodowanych odpowiednim nacisnieciem. 
*/
int read_touch(TypeMoney* moneyToSpend, TypeMoney* moneyToBet);

/* 
Wyswietlanie wiadomosci o zwyciezcy
*/
void displayWin(Player P);


/*
Samodzielna gra dealera
*/
bool DealerPlay(void);
	

#endif
