#include "main.h"
#include "adc.h"
#include "clcd.h"
//void glow_led(unsigned short adc_reg_val)

static void init_config(void)
{
	//LED1 = OFF;

	TRISB = 0;

    init_adc();
    //init_clcd();
}

void main(void)
{
    unsigned short adc_reg_val;

    init_config();

    while (1)
    {
        adc_reg_val = read_adc(CHANNEL4) / 10;
        //glow_led(adc_reg_val);

      //  char buff[5];
	//	unsigned char i;
		static unsigned short prog_cycle;
		static unsigned short duty_change;

		if(duty_change != adc_reg_val)
		{
			duty_change = adc_reg_val;
		}
	/*	i = 3;
		do
		{
			buff[i] = (adc_reg_val % 10) + '0';
			adc_reg_val = adc_reg_val / 10;
		} while (i--);
		buff[4] = '\0';

		clcd_print(buff, LINE2(0));

		//duty_change = 10;
	*/	if (prog_cycle < duty_change)
		{
			PORTB = 0xFF;
			//LED1 = ON;
		}
		else
		{
			PORTB = 0x00;
			//LED1 = OFF;
		}

		if (prog_cycle++ == 100)
		{
			prog_cycle = 0;
		}
    }
}
