#include "main.h"
#include "pic_specific.h"


void init_timer0(void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */
	//timer0 is congigured as an 8-Bit timer/counter
	T08BIT = 1;
	//internal instruction cycle clock(CLKO) as timer0 clock source
	T0CS = 0;
	//Timer0 prescaler is not assigned
	PSA = 1;
	//Loading timer register with intial value 6
	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	T0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;

	//keep pEIE bit high
	PEIE = 1;

	//TURN on timer 0
	TMR0ON = 1;
}
