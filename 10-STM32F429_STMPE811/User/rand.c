#include "rand.h"


uint8_t rand_function() {
	return ticks;
}


void cards_randomize(void) {
	sprintf(cardsSet, "234567891JQKA234567891JQKA234567891JQKA234567891JQKA");

	for (uint8_t i = 0; i < cardsSetSize; i++) {
		uint8_t rrand = (rand_function() + bet.value + budget.value) % (cardsSetSize - i);//rand (sys tick or sth)
		cards[i] = cardsSet[rrand];
		cardsSet[rrand] = cardsSet[cardsSetSize - 1 - i];
		cardsSet[cardsSetSize - 1 - i] = 0;
	}
}
