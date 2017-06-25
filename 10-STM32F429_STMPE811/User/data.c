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
