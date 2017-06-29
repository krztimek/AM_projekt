#ifndef LCD_H
#define LCD_H

#include "data.h"
#include "global_data.h"
/*
LCDInitialization - Inicjalizacja wyswietlacza LCD
*/
void LCDInitialization(void);

/*
draw_rectangle - Funkcja rysujaca prostokat o okreslonym ksztalcie
*/
void draw_rectangle(Rectangle rect, TM_FontDef_t *font, uint32_t color);

/*
Funkcja pozwalajaca odczytac dane z orzycisnietych element�w w czasie gry i wyb�r zmian w kartach spowodowanych odpowiednim nacisnieciem.
*/
int read_touch(TypeMoney* moneyToSpend, TypeMoney* moneyToBet);


#endif
