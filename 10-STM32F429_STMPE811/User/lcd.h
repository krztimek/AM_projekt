#ifndef LCD_H
#define LCD_H
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

/*
Funkcja wypisujaca na ekran struktury A1, B1 i C1, pokazuje na ekranie okreslone napisy
i przyciski w etapie wyboru wartosci budgetu i betu
*/
void print_choose(void);

/*
Funkcja wypisujaca gl�wne menu gry (new game, change bet i resign)
*/
void show_menu(void);

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
