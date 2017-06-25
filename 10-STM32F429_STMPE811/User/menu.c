#include "menu.h"


bool accept = true;

bool option1 = false;
bool option2 = false; 
bool option3 = false;

bool exitflag = false;

uint16_t start_value;
char cards [52] = "234567891JQKA234567891JQKA234567891JQKA234567891JQKA";
/*const uint8_t cardsSetSize = 52;
char cardsSet[cardsSetSize + 1] = "234567891JQKA234567891JQKA234567891JQKA234567891JQKA";//set of available cards, +1 because of '/0' at end
char cards[cardsSetSize];// here will be put random cards from cardsSet (function cards_randomize)
*/
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




void Draw_Rectangle(Rectangle rect, TM_FontDef_t *font, uint32_t color){
		TM_ILI9341_DrawFilledRectangle(rect.x, rect.y, rect.x+rect.length, rect.y+rect.width, color); 
		int a = strlen(rect.text);
		int x = rect.x + rect.length/2 -(font->FontWidth)*a/2;
		int y = rect.y + rect.width/2 - (font->FontHeight/2);
		TM_ILI9341_Puts(x, y, rect.text, font , ILI9341_COLOR_BLACK, color);
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
	
		Draw_Rectangle(A1, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
		Draw_Rectangle(B1, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
		Draw_Rectangle(C1, &TM_Font_11x18,ILI9341_COLOR_ORANGE);
	
}

void change_money(TypeMoney* Money) {
		while (accept) {
				sprintf(stringa, "Your %s = %i ", Money->type, Money->value);
				TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		/* If touch pressed */
		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
			/* Touch valid */

				if (touchData.x >= A1.x && touchData.x <= A1.x+A1.length && touchData.y >= A1.y && touchData.y <= A1.y+A1.width ){
						Money->value += 10; 
						Delayms(200);
						break;}
				
				else if (touchData.x >= B1.x && touchData.x <= B1.x+B1.length && touchData.y >= B1.y && touchData.y <= B1.y+B1.width ){
						Money->value -= 10;
						Delayms(200);
						break;}
			
				else if (touchData.x >= C1.x && touchData.x <= C1.x+C1.length && touchData.y >= C1.y && touchData.y <= C1.y+C1.width ){
						accept = false;
						Delayms(200);
						break;}
		}
	}
	if (Money->ifbudget == true) {
			start_value = Money->value;}
	
	accept = true;
}

void show_menu(void) {
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
		TM_ILI9341_Puts(70, 10, "MENU", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

	//sprintf(stringa, "Your %s = %i ",budget.type,tick );
		sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
		TM_ILI9341_Puts(20, 50, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

	
		Draw_Rectangle(A2, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
		Draw_Rectangle(B2, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
		Draw_Rectangle(C2, &TM_Font_11x18,ILI9341_COLOR_ORANGE);

}

void show_new_game(void){
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
		sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
		TM_ILI9341_Puts(20, 40, stringa, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
		TM_ILI9341_Puts(20, 55, stringa, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

		
		Draw_Rectangle(D, &TM_Font_7x10, ILI9341_COLOR_ORANGE);
		Draw_Rectangle(E, &TM_Font_7x10, ILI9341_COLOR_ORANGE);
		Draw_Rectangle(F, &TM_Font_7x10,ILI9341_COLOR_ORANGE);


		Delayms(50);
}

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
				sprintf(stringa, "You won: %i ", budget.value - start_value);}
		else {
				sprintf(stringa, "You lost: %i ", budget.value - start_value);}
		
		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
		TM_ILI9341_Puts(50, 110, "Thank you!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

		while (1);
}



/*
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
=======
*/
void Cards_Randomize(void){
	
		char a;
		int ticks = tick_from_systick;
		for (uint8_t i = 1; i<100; i++){
				for (uint8_t j=1; j<50; j++){
						a = cards[(i+j+ticks)%52]; 
						cards[(i+j+ticks)%52] = cards[(i*j*ticks)%52];
						cards[(i*j*ticks)%52] = a;
				}
		}
}


int StringToPoint(int index) {
		switch ((char)cards[index]) {
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
				default: return 0; break;
		}

}


void ShowCards(Player* P, int iterator){
		char cards_of_player [10] = "";
		//char cards_of_dealer [10] = "";
		//int player_points = 0;
		//int dealer_points = 0;
		P->points = 0;
		int x = 0;
		char string1[10] = "";
		char string2[10] = "";
		int aces = 0;
		for (int i = P->start_index; i<= iterator; i++){
				if (P->ifdealer == false){
						x = 120;
						cards_of_player [i-P->start_index] = cards [i];
				}	
				else{
						x = 80;
						cards_of_player [i] = cards [i];}
			
				if (cards [i] == 'A'){
							aces +=1;
				}
				P->points +=StringToPoint(i);
			
		}
		if ((P->points > 21) && (aces != 0)){
				
				for (int i = 0; i < aces ; i++ ){
						P->points -= 10;
						if (P->points <= 21) {
								break;
						}
				}
		}
		sprintf(string1, "%s cards: %s ",P->name, cards_of_player);
		TM_ILI9341_Puts(20, x, string1, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		sprintf(string2, "%s points: %i ",P->name, P->points);
		TM_ILI9341_Puts(20, x+20, string2, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		Delayms(50);
}

int read_touch(TypeMoney* moneyToSpend, TypeMoney* moneyToBet){
		while(1){
		
				while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed) {
				/* Touch valid */
				Delayms(50);
				if (touchData.x >= D.x && touchData.x <= D.x+D.length && touchData.y >= D.y && touchData.y <= D.y+D.width){ //Wybrana opcja "Hit"
						return 1;
	
				}
				else if (touchData.x >= E.x && touchData.x <= E.x+E.length && touchData.y >= E.y && touchData.y <= E.y+E.width ){ //Wybrana opcja "Double"
						if (moneyToSpend->value > moneyToBet->value*2) {
								moneyToBet -> value = moneyToBet->value*2;
								exitflag = true;
								return 1;
						}
						else {
								moneyToBet -> value = moneyToSpend->value;
								exitflag = true;
								return 1;
						}
				}
				else if (touchData.x >= F.x && touchData.x <= F.x+F.length && touchData.y >= F.y && touchData.y <= F.y+F.width ){ //Wybrana opcja "Stand"
						exitflag = true;
						return 0;
				}
				else {
				;}	
				}

		}

}
bool DealerPlay(void){
		int dealerIndicator = dealer.start_index +1; 
		while (1) {
				ShowCards(&dealer, dealerIndicator);
				if ((dealer.points <= 21)&&(dealer.points > player.points)) {
						return true; 	}
				else if (dealer.points > 21){
						return false; }
				else {
						dealerIndicator++;}
				Delayms(500);
		}

}

void displayWin(Player P){
		char string1[10];
		if (P.ifdealer == true){
				sprintf(string1, "YOU LOST!");}
		else {
				sprintf(string1, "YOU WON!");}
		
		TM_ILI9341_Puts(90, 175, string1, &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_WHITE);

}

void PlayCards(TypeMoney* moneyToSpend, TypeMoney* moneyToBet){
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
		int dealerIndicator = dealer.start_index;
		int playerIndicator = player.start_index + 1;
		for (int i = 0; i<10; i++){Cards_Randomize();}
				while (1){
						show_new_game();

						ShowCards(&dealer, dealerIndicator);
						ShowCards(&player, playerIndicator);
						if (player.points == 21) {
								displayWin(player);
								moneyToSpend->value += moneyToBet->value;
								Delayms(2000);
								break;
						}
						else if (player.points > 21){
								displayWin(dealer);
								moneyToSpend->value -= moneyToBet->value;
								Delayms(2000);
								break;
						}
				
						if (exitflag == true){
								bool winner = DealerPlay();
								if (winner == true) {
										displayWin(dealer);
										moneyToSpend->value -= moneyToBet->value;}
								
								else {
										displayWin(player);
										moneyToSpend->value += moneyToBet->value;}
						
								exitflag = false;
								Delayms(2000);
								break;
						}
			
				playerIndicator += read_touch(moneyToSpend, moneyToBet);
			
				//Delayms(300);

				//a++;
				}
}


