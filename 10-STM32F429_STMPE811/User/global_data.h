#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

extern bool accept;

extern bool option1;
extern bool option2;
extern bool option3;

extern bool exitflag;

extern uint16_t start_value;
extern const uint8_t cardsSetSize;
extern char cardsSet[cardsSetSize + 1];//set of available cards, +1 because of '/0' at end
extern char cards[cardsSetSize];// here will be put random cards from cardsSet (function cards_randomize)

extern char stringa[30];

extern volatile uint32_t tick_from_systick;

extern TypeMoney budget;
extern TypeMoney bet;
extern Player dealer;
extern Player player;

extern Rectangle A1;
extern Rectangle B1;
extern Rectangle C1;
extern Rectangle A2;
extern Rectangle B2;
extern Rectangle C2;
extern Rectangle D;
extern Rectangle E;
extern Rectangle F;

extern TM_STMPE811_TouchData touchData;

#endif
