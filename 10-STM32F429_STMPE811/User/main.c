/**
 *	Keil project for STMPE811 touch driver controller
 *
 *	Works on STM32F429 Discovery board by default
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 */


/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "menu.h"


#include <stdio.h>
#include "core.h"
#include "lcd.h"

extern TypeMoney budget;
extern TypeMoney bet;
extern bool option1;
extern bool option2;
extern bool option3;
extern int ticks;

void SystickHandler(void){
	ticks++;
}

int main(void) {
  SysTick_Config(SystemCoreClock / 1000);
	LCDInitialization();
	print_choose();
	change_money(&budget);
	print_choose();
	change_money(&bet);
	while(1) {
		show_menu();
		change_menu();

		if (option1 == true){
		  play_cards(&budget, &bet);
			option1 = false;
		}
		if(option2 == true){
			print_choose();
			change_money(&bet);
			option2 = false;
		}
		if (option3 == true){
			exit_game();
		}
	}
}
