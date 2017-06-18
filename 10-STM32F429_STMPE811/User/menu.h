#ifndef __menu_h
#define __menu_h

#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_stmpe811.h"
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include "cards.h"


typedef struct {
	int value;
	char type[10];
	bool ifbudget;
} TypeMoney;


typedef struct {
char name[16];
uint8_t start_index;
bool ifdealer;
char cardset[10]; 
} Player;

uint8_t rand_function(void);
void cards_randomize(void);

int StringToPoint(int index);
void ShowCards( Player player);
void PlayCards(TypeMoney A, TypeMoney B);

void LCDInitialization(void);
void print_choose(void);
void change_money(TypeMoney* Money);
void show_menu(void);
void change_menu(void);
void exit_game(void);
void Play(void);

#endif

