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


void draw_rectangle(Rectangle rect, TM_FontDef_t *font, uint32_t color){
	TM_ILI9341_DrawFilledRectangle(rect.x, rect.y, rect.x+rect.length, rect.y+rect.width, color);
	int a = strlen(rect.text);
	int x = rect.x + rect.length/2 -(font->FontWidth)*a/2;
	int y = rect.y + rect.width/2 - (font->FontHeight/2);
	TM_ILI9341_Puts(x, y, rect.text, font , ILI9341_COLOR_BLACK, color);
}


int read_touch(TypeMoney* moneyToSpend, TypeMoney* moneyToBet){
	while(1){//wait for touch
		while (TM_STMPE811_ReadTouch(&touchData) == TM_STMPE811_State_Pressed){
			/* Touch valid */
			Delayms(50);
			if (touchData.x >= D.x && touchData.x <= D.x+D.length && touchData.y >= D.y && touchData.y <= D.y+D.width){ //Wybrana opcja "Hit"
				return 1;
			}
			else if (touchData.x >= E.x && touchData.x <= E.x+E.length && touchData.y >= E.y && touchData.y <= E.y+E.width ){ //Wybrana opcja "Double"
				if (moneyToSpend->value > moneyToBet->value*2){
					moneyToBet -> value = moneyToBet->value*2;
					exitflag = true;
					return 1;
				}
				else{
					moneyToBet -> value = moneyToSpend->value;
					exitflag = true;
					return 1;
				}
			}
			else if (touchData.x >= F.x && touchData.x <= F.x+F.length && touchData.y >= F.y && touchData.y <= F.y+F.width ){ //Wybrana opcja "Stand"
					exitflag = true;
					return 0;
			}
		}
	}
}


void print_choose(void) {
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(10, 10, "Welcome in BlackJack", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

	draw_rectangle(A1, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
	draw_rectangle(B1, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
	draw_rectangle(C1, &TM_Font_11x18,ILI9341_COLOR_ORANGE);
}


void show_menu(void) {
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(70, 10, "MENU", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);

//sprintf(stringa, "Your %s = %i ",budget.type,tick );
	sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
	TM_ILI9341_Puts(20, 50, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
	TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

	draw_rectangle(A2, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
	draw_rectangle(B2, &TM_Font_11x18, ILI9341_COLOR_ORANGE);
	draw_rectangle(C2, &TM_Font_11x18,ILI9341_COLOR_ORANGE);
}


void show_new_game(void){
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
		sprintf(stringa, "Your %s = %i ",budget.type,budget.value );
		TM_ILI9341_Puts(20, 40, stringa, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
		sprintf(stringa, "Your %s = %i ",bet.type,bet.value );
		TM_ILI9341_Puts(20, 55, stringa, &TM_Font_7x10, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);

		draw_rectangle(D, &TM_Font_7x10, ILI9341_COLOR_ORANGE);
		draw_rectangle(E, &TM_Font_7x10, ILI9341_COLOR_ORANGE);
		draw_rectangle(F, &TM_Font_7x10,ILI9341_COLOR_ORANGE);

		Delayms(50);
}


void show_cards(Player* P, int iterator){
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
			cards_of_player [i] = cards [i];
		}

		if (cards [i] == 'A'){
					aces +=1;
		}

		P->points += string_to_point(i);
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


void display_win(Player P){
	char string1[10];
	if(P.ifdealer == true){
		sprintf(string1, "YOU LOST!");}
	else{
		sprintf(string1, "YOU WON!");
	}
	TM_ILI9341_Puts(90, 175, string1, &TM_Font_11x18, ILI9341_COLOR_RED, ILI9341_COLOR_WHITE);
}
