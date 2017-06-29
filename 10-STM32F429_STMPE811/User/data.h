#ifndef DATA_H
#define DATA_H

#include "stdbool.h"
#include "stdint.h"
#include "tm_stm32f4_stmpe811.h"


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

#endif
