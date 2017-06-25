#ifndef __menu_h
#define __menu_h

#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_stmpe811.h"
#include <stdbool.h>
#include <stdio.h>
#include "cards.h"
#include "core.h"
#include "lcd.h"
#include "data.h"

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
Funkcja wypisujaca gl�wne menu gry (new game, change bet i resign)
*/
void show_menu(void);

/*
Funkcja pozwalajaca za pomoca odpowiedniej zmiennej wejsc w dany etap menu.
*/
void change_menu(void);


/*
New game screen
*/
void show_new_game(void);

/*
show_cards - Funkcja wypisujaca na ekran karty i ilosc punkt�w danego uzytkownika
Player P - zawodnik lub dealer
iterator - ilosc kart, kt�re nalezy wypisac
*/
void show_cards(Player* P, int iterator);

/*
Wyswietlanie wiadomosci o zwyciezcy
*/
void display_win(Player P);


#endif
