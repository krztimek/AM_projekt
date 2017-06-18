#include "menu.h"


bool accept = true;
bool game = false;
bool betchange = false;
bool resign = false;


uint16_t start_value;
const uint8_t cardsSetSize = 52;
char cardsSet[cardsSetSize + 1] = "234567891JQKA234567891JQKA234567891JQKA234567891JQKA";//set of available cards, +1 because of '/0' at end
char cards[cardsSetSize];// here will be put random cards from cardsSet (function cards_randomize)
char stringa[30];

int ticks = 0;

TypeMoney budget = {.value = 100, .type = "budget", .ifbudget = true};
TypeMoney bet = {.value = 10, .type = "bet", .ifbudget = false};
Player dealer = {.name = "Dealer", .start_index = 0, .ifdealer = true };
Player player = {.name = "Player", .start_index = 26, .ifdealer = false };


Rectangle A = {.x = 10, .y = 170, .length = 210, .width = 40, .text = "+" };
Rectangle B = {.x = 10, .y = 220, .length = 210, .width = 40, .text = "-"};
Rectangle C = {.x = 10, .y = 270, .length = 210, .width = 40, .text = "ACCEPT" };
Rectangle D = {.x = 10, .y = 200, .length = 70, .width = 100, .text = "Hit" };
Rectangle E = {.x = 90, .y = 200, .length = 70, .width = 100, .text = "Double" };
Rectangle F = {.x = 170, .y = 200, .length = 70, .width = 100, .text = "Stand"};


TM_STMPE811_TouchData touchData;



void Draw_Rectangle(Rectangle rect, uint32_t color){
		TM_ILI9341_DrawFilledRectangle(rect.x, rect.y, rect.x+rect.length, rect.y+rect.width, color);
		TM_ILI9341_Puts(rect.length/2, rect.y+rect.width/3, rect.text, &TM_Font_11x18, ILI9341_COLOR_BLACK, color);
}

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
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);

	/* Initialize Touch */
	if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
		TM_ILI9341_Puts(20, 20, "STMPE811 Error", &TM_Font_11x18, ILI9341_COLOR_ORANGE, ILI9341_COLOR_BLACK);

		while (1);
	}

	/* Select touch screen orientation */
	touchData.orientation = TM_STMPE811_Orientation_Portrait_2;

}

void print_choose(void) {
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(10, 10, "Welcome in BlackJack", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

	Draw_Rectangle(A, ILI9341_COLOR_ORANGE);
	Draw_Rectangle(B, ILI9341_COLOR_ORANGE);
	Draw_Rectangle(C, ILI9341_COLOR_ORANGE);


}

void change_money(TypeMoney* Money) {
	while (accept) {
		sprintf(stringa, "Your %s = %i ", Money->type, Money->value);
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		/* If touch pressed */
		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */
			if (touchData.x >= A.x && touchData.x <= A.x+A.length && touchData.y >= A.y && touchData.y <= A.y+A.width ){
				Money->value += 10;
				Delayms(200);
				break;
			}
			else if (touchData.x >= B.x && touchData.x <= B.x+B.length && touchData.y >= B.y && touchData.y <= B.y+B.width ){
				Money->value -= 10;
				Delayms(200);
				break;
			}
			else if (touchData.x >= C.x && touchData.x <= C.x+C.length && touchData.y >= C.y && touchData.y <= C.y+C.width ){
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

void show_menu(void) {
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(70, 10, "MENU", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

	sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
		TM_ILI9341_Puts(20, 50, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

	TM_ILI9341_DrawFilledRectangle(A.x, A.y, A.x+A.length, A.y+A.width, ILI9341_COLOR_ORANGE);
	TM_ILI9341_Puts(A.length/2, A.y+A.width/3, "New game", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
	TM_ILI9341_DrawFilledRectangle(B.x, B.y, B.x+B.length, B.y+B.width, ILI9341_COLOR_ORANGE);
	TM_ILI9341_Puts(B.length/2, B.y+B.width/3, "Change bet", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
	TM_ILI9341_DrawFilledRectangle(C.x, C.y, C.x+C.length, C.y+C.width, ILI9341_COLOR_ORANGE);
	TM_ILI9341_Puts(C.length/2, C.y+C.width/3, "Resign", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_YELLOW);
}

void show_new_game(void){
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
		TM_ILI9341_Puts(20, 40, stringa, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
		TM_ILI9341_Puts(20, 55, stringa, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

	TM_ILI9341_DrawFilledRectangle(D.x, D.y, D.x+D.length, D.y+D.width, ILI9341_COLOR_ORANGE);
	TM_ILI9341_Puts(D.length/2, D.y+D.width/3, "Add", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	TM_ILI9341_DrawFilledRectangle(E.x, E.y, E.x+E.length, E.y+E.width, ILI9341_COLOR_ORANGE);
	TM_ILI9341_Puts(E.x +E.length/4, E.y+E.width/3, "Double", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	TM_ILI9341_DrawFilledRectangle(F.x, F.y, F.x+F.length, F.y+F.width, ILI9341_COLOR_ORANGE);
	TM_ILI9341_Puts(F.x + F.length/4, F.y+F.width/3, "Resign", &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);


}

void change_menu(void) {


	while (accept) {

		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */

			if (touchData.x >= A.x && touchData.x <= A.x+A.length && touchData.y >= A.y && touchData.y <= A.y+A.width){
				game = true;
				accept = false;
				break;
			}
			else if (touchData.x >= B.x && touchData.x <= B.x+B.length && touchData.y >= B.y && touchData.y <= B.y+B.width ){
				betchange = true;
				accept = false;
				break;
			}
			else if (touchData.x >= C.x && touchData.x <= C.x+C.length && touchData.y >= C.y && touchData.y <= C.y+C.width ){
				resign = true;
				accept = false;
				break;
			}
			else {
				;
			}
		}
	}
	accept = true;
}

void exit_game(void) {

	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	if (budget.value >= start_value) {
		sprintf(stringa, "You won: %i ", budget.value - start_value);
	}
	else {
		sprintf(stringa, "You lost: %i ", budget.value - start_value);
	}
	TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
	TM_ILI9341_Puts(50, 110, "Thank you!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
	while (1);
}




uint8_t rand_function() {//TBD
	return 10;
}

void cards_randomize(void) {
	for (uint8_t i = 0; i < cardsSetSize; i++) {
		uint8_t rrand = rand_function() % (cardsSetSize - i);//rand (sys tick or sth)
		cards[i] = cardsSet[rrand];
		cardsSet[rrand] = cardsSet[cardsSetSize - 1 - i];
		cardsSet[cardsSetSize - 1 - i] = 0;
	}
	for (int i = 0; i<10; i++) {//10 ?? possible 11 cards as winer AAAA 2222 333 = 4 + 8 + 9 = 21
		(dealer.cardset)[i] = '\0';
		(player.cardset)[i] = '\0';
	}
}


int StringToPoint(int index) {
		if (cards [index] == 'A'){
		return 11;}
		else if (cards [index] == '2'){
		return 2;}
		else if (cards [index] == '3'){
		return 3;}
		else if (cards [index] == '4'){
		return 4;}
		else if (cards [index] == '5'){
		return 5;}
		else if (cards [index] == '6'){
		return 6;}
		else if (cards [index] == '7'){
		return 7;}
		else if (cards [index] == '8'){
		return 8;}
		else if (cards [index] == '9'){
		return 9;}
		else if (cards [index] == 'K'|| cards [index] == 'Q' || cards [index] == 'J' || cards [index] == '1'){
		return 10;}
		else {
		return 0;}

}



void ShowCards(Player P, int iterator){
	char cards_of_player [10] = "";
	char cards_of_dealer [10] = "";
	int player_points = 0;
	int dealer_points = 0;
	int x = 80;
	char string1[10];
	char string2[10];


	if (P.ifdealer == true){
			for (int i = P.start_index; i<= iterator; i++){
					cards_of_dealer [i] = cards [i];
					dealer_points +=StringToPoint(i);
			}
			sprintf(string1, "%s cards: %s ",P.name, cards_of_dealer);
			TM_ILI9341_Puts(20, x, string1, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
			sprintf(string2, "%s points: %i ",P.name, dealer_points);
			TM_ILI9341_Puts(20, x+20, string2, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

		}
		else {
			x+=40;
			for (int i = P.start_index; i<= iterator; i++){
					cards_of_player [i-P.start_index] = cards [i];
					player_points +=StringToPoint(i);
			}
			sprintf(string1, "%s cards: %s ",P.name, cards_of_player);
			TM_ILI9341_Puts(20, x, string1, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
			sprintf(string2, "%s points: %i ",P.name, player_points);
			TM_ILI9341_Puts(20, x+20, string2, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		}
}

void PlayCards(TypeMoney* A, TypeMoney* B){
			TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
			int a = dealer.start_index;
			int b = player.start_index;
			for (int i = 0; i<10; i++){Cards_Randomize();}
			while (1){
			show_new_game();
			ShowCards(dealer, a);
			ShowCards(player, b);

				Delayms(5000);
				//a++;
			}
}
