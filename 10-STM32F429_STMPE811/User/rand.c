#include "rand.h"


uint8_t rand_function() {
	return tick_from_systick;
}


void cards_randomize(void) {
	for (uint8_t i = 0; i < cardsSetSize; i++) {
		uint8_t rrand = rand_function() % (cardsSetSize - i);//rand (sys tick or sth)
		cards[i] = cardsSet[rrand];
		cardsSet[rrand] = cardsSet[cardsSetSize - 1 - i];
		cardsSet[cardsSetSize - 1 - i] = 0;
	}
	for (int i = 0; i<20; i++) {//10 ?? possible 11 cards as winer AAAA 2222 333 = 4 + 8 + 9 = 21
		(dealer.cardset)[i] = '\0';
		(player.cardset)[i] = '\0';
}
