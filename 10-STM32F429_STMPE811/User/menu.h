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
Funkcja StringToPoint - zamiana karry na przypisana do niej ilosc punkt�w
*/
int StringToPoint(int index);

/*
ShowCards - Funkcja wypisujaca na ekran karty i ilosc punkt�w danego uzytkownika
Player P - zawodnik lub dealer
iterator - ilosc kart, kt�re nalezy wypisac
*/
void ShowCards(Player P, int iterator);

/*
PlayCards - Funkcja w kt�rej okreslona jest cala funkcjonalnosc gry
*/
void PlayCards(TypeMoney* A, TypeMoney* B);

/*
Draw_Rectangle - Funkcja rysujaca prostokat o okreslonym ksztalcie
*/
void Draw_Rectangle(Rectangle rect, uint32_t color);

/*
LCDInitialization - Inicjalizacja wyswietlacza LCD
*/
void LCDInitialization(void);


void print_choose(void);


void change_money(TypeMoney* Money);


void show_menu(void);


void change_menu(void);


void exit_game(void);


#endif
