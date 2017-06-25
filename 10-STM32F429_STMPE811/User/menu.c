#include "menu.h"

bool accept = true;

bool option1 = false;
bool option2 = false;
bool option3 = false;

bool exitflag = false;

uint16_t start_value;
const uint8_t cardsSetSize = 52;
char cardsSet[cardsSetSize + 1] = "234567891JQKA234567891JQKA234567891JQKA234567891JQKA";//set of available cards, +1 because of '/0' at end
char cards[cardsSetSize];// here will be put random cards from cardsSet (function cards_randomize)

char stringa[30];

extern volatile uint32_t tick_from_systick;

TypeMoney budget = {.value = 100, .type = "budget", .ifbudget = true};
TypeMoney bet = {.value = 10, .type = "bet", .ifbudget = false};
Player dealer = {.name = "Dealer", .start_index = 0, .points = 0, .ifdealer = true };
Player player = {.name = "Player", .start_index = 26, .points = 0, .ifdealer = false };


Rectangle A1 = {.x = 10, .y = 170, .length = 210, .width = 40, .text = "+" };
Rectangle B1 = {.x = 10, .y = 220, .length = 210, .width = 40, .text = "-"};
Rectangle C1 = {.x = 10, .y = 270, .length = 210, .width = 40, .text = "ACCEPT" };
Rectangle A2 = {.x = 10, .y = 170, .length = 210, .width = 40, .text = "New Game" };
Rectangle B2 = {.x = 10, .y = 220, .length = 210, .width = 40, .text = "Change bet"};
Rectangle C2 = {.x = 10, .y = 270, .length = 210, .width = 40, .text = "Resign" };
Rectangle D = {.x = 10, .y = 200, .length = 70, .width = 100, .text = "Hit" };
Rectangle E = {.x = 90, .y = 200, .length = 70, .width = 100, .text = "Double" };
Rectangle F = {.x = 170, .y = 200, .length = 70, .width = 100, .text = "Stand"};


TM_STMPE811_TouchData touchData;




void change_menu(void) {
	while (accept) {
		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */
			if (touchData.x >= A2.x && touchData.x <= A2.x+A2.length && touchData.y >= A2.y && touchData.y <= A2.y+A2.width){
				option1 = true;
				accept = false;
				break;
			}
			else if (touchData.x >= B2.x && touchData.x <= B2.x+B2.length && touchData.y >= B2.y && touchData.y <= B2.y+B2.width ){
				option2 = true;
				accept = false;
				break;
			}
			else if (touchData.x >= C2.x && touchData.x <= C2.x+C2.length && touchData.y >= C2.y && touchData.y <= C2.y+C2.width ){
				option3 = true;
				accept = false;
				break;
			}
		}
	}

	accept = true;
}


void change_money(TypeMoney* Money) {
	while (accept) {
		sprintf(stringa, "Your %s = %i ", Money->type, Money->value);
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	  /* If touch pressed */
	  while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */
			if (touchData.x >= A1.x && touchData.x <= A1.x+A1.length && touchData.y >= A1.y && touchData.y <= A1.y+A1.width ){
				if(Money->ifbudget == false){//bet maximum is budget
					if(bet->value < budget->value){
						Money->value += 10;
					}
					else{
						sprintf(string1, "Not engouh money!");
						TM_ILI9341_Puts(90, 100, string1, &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_WHITE);//not engouh money
					}
				}
				else{
					Money->value += 10;
				}
					Delayms(200);
					break;
			}
			else if (touchData.x >= B1.x && touchData.x <= B1.x + B1.length && touchData.y >= B1.y && touchData.y <= B1.y + B1.width ){
					Money->value -= 10;
					Delayms(200);
					break;
			}
			else if (touchData.x >= C1.x && touchData.x <= C1.x + C1.length && touchData.y >= C1.y && touchData.y <= C1.y + C1.width ){
					accept = false;
					Delayms(200);
					break;
			}
		}
	}

	if (Money->ifbudget == true) {
			start_value = Money->value;
	}
	accept = true;
}
