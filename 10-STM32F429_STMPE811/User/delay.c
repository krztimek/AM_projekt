#include "stm32f4xx.h"
#include "delay.h"
static volatile uint32_t tick =0;

void delay(uint32_t delayInMiliseconds)
{
	
	uint32_t endTick = tick + delayInMiliseconds;
	while(tick < endTick){;}
		
} /* delay */

/**
 * System Tick Interrupt Service Routine 

void SysTick_Handler(void)
{
	tick++;
} */ /* SysTick_Handler */
