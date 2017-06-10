#include "menu.h"


bool accept = true;
bool game = false;
bool betchange = false; 
bool resign = false;

uint16_t start_value;
uint8_t rrand = 10;
char cards[52] = "234567891JQKA234567891JQKA234567891JQKA234567891JQKA";
char stringa[30];


TypeMoney budget = {.value = 100, .type = "budget", .ifbudget = true};
TypeMoney bet = {.value = 10, .type = "bet", .ifbudget = false};
Player dealer = {.name = "Dealer", .start_index = 0, .ifdealer = true };
Player player = {.name = "Player", .start_index = 50, .ifdealer = false };

TM_STMPE811_TouchData touchData;





void LCDInitialization(){
/* Initialize system */
	SystemInit();
	
	/* Initialize LCD */
	TM_ILI9341_Init();
	
	/* Initialize delay */
	TM_DELAY_Init();
	
	/* Rotate LCD */
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Portrait_2);
	
	/* Fill with orange color */
//	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	
	/* Initialize Touch */
	if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
		TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);
		
		while (1);
	}
	
	/* Select touch screen orientation */
	touchData.orientation = TM_STMPE811_Orientation_Portrait_2;
	
}

void print_choose(void){
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(10, 10, "Welcome in BlackJack", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
	
	TM_ILI9341_DrawFilledRectangle(10, 120, 220, 160, ILI9341_COLOR_ORANGE); 
	TM_ILI9341_Puts(100, 135, "+", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	TM_ILI9341_DrawFilledRectangle(10, 170, 220, 210, ILI9341_COLOR_ORANGE); 
	TM_ILI9341_Puts(100, 185, "-", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	TM_ILI9341_DrawFilledRectangle(10, 220, 220, 260, ILI9341_COLOR_ORANGE); 
	TM_ILI9341_Puts(70, 235, "ACCEPT", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
}

void change_money(TypeMoney* Money){
	while (accept) {
		sprintf(stringa, "Your %s = %i ",Money->type,Money->value );
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		/* If touch pressed */
		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */
			if (touchData.x >= 10 && touchData.x <= 220 && touchData.y >= 120 && touchData.y <= 160 ){
				Money->value += 10; 
				Delayms(200);
				break;
			}
			else if (touchData.x >= 10 && touchData.x <= 220 && touchData.y >= 170 && touchData.y <= 210 ){
				Money->value -= 10;
				Delayms(200);
				break;
			}
			else if (touchData.x >= 10 && touchData.x <= 220 && touchData.y >= 220 && touchData.y <= 260 ){
				accept = false;
				Delayms(200);
				break;
			}
		}
	}
	if (Money->ifbudget == true){
	start_value = Money->value;
	}
	accept = true;
}

void show_menu(void){
  TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(70, 10, "MENU", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
	
	sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
		TM_ILI9341_Puts(20, 50, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	
	TM_ILI9341_DrawFilledRectangle(10, 120, 220, 160, ILI9341_COLOR_YELLOW); 
	TM_ILI9341_Puts(70, 135, "New game", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
	TM_ILI9341_DrawFilledRectangle(10, 170, 220, 210, ILI9341_COLOR_YELLOW); 
	TM_ILI9341_Puts(70, 185, "Change bet", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
	TM_ILI9341_DrawFilledRectangle(10, 220, 220, 260, ILI9341_COLOR_YELLOW); 
	TM_ILI9341_Puts(70, 235, "Resign", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
}

void change_menu(void){
	
	
	while(accept){
		
		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */
	
			if (touchData.x >= 10 && touchData.x <= 220 && touchData.y >= 120 && touchData.y <= 160 ){
				game = true;
				accept = false;
				break;
			}
			else if (touchData.x >= 10 && touchData.x <= 220 && touchData.y >= 170 && touchData.y <= 210 ){
				betchange = true;
				accept = false;
				break;
			}
			else if (touchData.x >= 10 && touchData.x <= 220 && touchData.y >= 220 && touchData.y <= 260 ){
				resign = true;
				accept = false;
				break;
			}
			else {
			;}	
		}
	}
	
	accept = true;
}

void exit_game(void){

	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	if (budget.value >= start_value){
		sprintf(stringa, "You won: %i ",budget.value - start_value );
	}
	else{
		sprintf(stringa, "You lost: %i ",budget.value - start_value );
	}
	TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
	TM_ILI9341_Puts(50, 110, "Thank you!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
	while (1);
}



void Cards_Randomize(void){
	rrand = rrand%26;
	for (uint8_t i = 1; i<10; i++){
		rrand++;
		for (uint8_t j=1; j<10; j++){
				cards[(i+j+rrand)%52] ^= cards[(i*j+rrand)%52];
				cards[(i*j+rrand)%52] ^= cards[(i+j+rrand)%52];
				cards[(i+j+rrand)%52] ^= cards[(i*j+rrand)%52];
		}
	}
	for (int i = 0; i<10; i++){
		(dealer.cardset)[i] = '\0';
		(player.cardset)[i] = '\0';
	}
	
}


int StringToPoint(int index) {
	switch (cards[index]) {
	case 50: return 2; break;
	case 51: return 3; break;
	case 52: return 4; break;
	case 53: return 5; break; 
	case 54: return 6; break;
	case 55: return 7; break;
	case 56: return 8; break;
	case 57: return 9; break;
	case 49: return 10; break;
	case 74: return 10; break;
	case 81: return 10; break;
	case 75: return 10; break;
	case 65: return 11; break;
	}
}



void ShowCards(Player P){
		if (P.ifdealer == true){
		
		}
			
		else {
		}

}

void PlayCards(TypeMoney BUdget, TypeMoney Bet){
		




}
