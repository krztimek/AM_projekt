/* Includes ------------------------------------------------------------------*/
#include "core.h"


int string_to_point(int index) {
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


void play_cards(TypeMoney* moneyToSpend, TypeMoney* moneyToBet){
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	int dealerIndicator = dealer.start_index;
	int playerIndicator = player.start_index + 1;
	cards_randomize();
	while (1){
		if(moneyToSpend->value <= 0){
			exit_game();
		}
		if(moneyToBet->value > moneyToSpend->value){
			print_choose();
			change_money(&bet);
		}

		show_new_game();
		show_cards(&dealer, dealerIndicator);
		show_cards(&player, playerIndicator);

		if (player.points == 21){
			display_win(player);
			moneyToSpend->value += moneyToBet->value;
			Delayms(2000);
			break;
		}
		else if (player.points > 21){
			display_win(dealer);
			moneyToSpend->value -= moneyToBet->value;
			Delayms(2000);
			break;
		}

		if (exitflag == true){
			bool dealerWins = dealer_play();
			if (dealerWins == true){
				display_win(dealer);
				moneyToSpend->value -= moneyToBet->value;
			}
			else{
				display_win(player);
				moneyToSpend->value += moneyToBet->value;
			}
			if (moneyToSpend->value == 0){
				Delayms(2000);
				exit_game();
			}
			exitflag = false;
			Delayms(2000);
			break;
		}

		playerIndicator += read_touch(moneyToSpend, moneyToBet);
	//Delayms(300);
	//a++;
	}
}


bool dealer_play(void){
	int dealerIndicator = dealer.start_index +1;
	while (1){
		show_cards(&dealer, dealerIndicator);
		if ((dealer.points <= 21)&&(dealer.points > player.points)){
			return true;
		}
		else if (dealer.points > 21){
			return false;
		}
		else{
			dealerIndicator++;}
		Delayms(2000);
		}
}


void exit_game(void){
	
	uint16_t position = 0;
	
	while (1){
		TM_ILI9341_Fill(ILI9341_COLOR_GREEN);

		if (budget.value >= start_value){
			sprintf(stringa, "You won: $%i", budget.value - start_value);
		}
		else{
			sprintf(stringa, "You lost: $%i", start_value - budget.value);
		}

		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
		TM_ILI9341_Puts(position % 110, 110 + position % 30, "Thank you!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_RED);
		position += 10;
		Delayms(100);
		TM_ILI9341_Fill(ILI9341_COLOR_RED);

		if (budget.value >= start_value){
			sprintf(stringa, "You won: $%i", budget.value - start_value);
		}
		else{
			sprintf(stringa, "You lost: $%i", start_value - budget.value);
		}

		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
		TM_ILI9341_Puts(position % 110, 110 + position % 60, "Thank you!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
		position += 10;
		Delayms(100);
		
		TM_ILI9341_Fill(ILI9341_COLOR_BLUE);

		if (budget.value >= start_value){
			sprintf(stringa, "You won: $%i", budget.value - start_value);
		}
		else{
			sprintf(stringa, "You lost: $%i", start_value - budget.value);
		}

		TM_ILI9341_Puts(20, 80, stringa, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN);
		TM_ILI9341_Puts(position % 110, 110 + position % 90, "Thank you!", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN);
		position += 10;
		Delayms(100);
	}
}
