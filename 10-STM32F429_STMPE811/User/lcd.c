#include "lcd.h"

extern Rectangle D;
extern Rectangle E;
extern Rectangle F;

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
