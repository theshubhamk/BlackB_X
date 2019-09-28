#include "pic_specific.h"
#include "main.h"
#include "clcd.h"
#include "ds1307.h"
#include "matrix_keypad.h"
#include "timer0.h"
#include "adc.h"


unsigned char clock_reg[3];
unsigned char calender_reg[4];
unsigned char time[9];
unsigned char date[11];

void display_date(void)
{
	clcd_print(date, LINE2(3));
}

void display_time(void)
{
	clcd_print(time, LINE2(0));

	/*if (clock_reg[0] & 0x40)
	{
		if (clock_reg[0] & 0x20)
		{
			clcd_print("PM", LINE2(12));
		}
		else
		{
			clcd_print("AM", LINE2(12));
		}
	}*/
}

static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[0] &= 0xF0;
	clock_reg[0] |= 0x06;

	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

static void get_date(void)
{
	calender_reg[0] = read_ds1307(YEAR_ADDR);
	calender_reg[1] = read_ds1307(MONTH_ADDR);
	calender_reg[2] = read_ds1307(DATE_ADDR);
	calender_reg[3] = read_ds1307(DAY_ADDR);

	date[0] = '2';
	date[1] = '0';
	date[2] = '0' + ((calender_reg[0] >> 4) & 0x0F);
	date[3] = '0' + (calender_reg[0] & 0x0F);
	date[4] = '-';
	date[5] = '0' + ((calender_reg[1] >> 4) & 0x0F);
	date[6] = '0' + (calender_reg[1] & 0x0F);
	date[7] = '-';
	date[8] = '0' + ((calender_reg[2] >> 4) & 0x0F);
	date[9] = '0' + (calender_reg[2] & 0x0F);
	date[10] = '\0';
}

void init_config(void)
{
	/* Clear old content */
	PORTB = 0x00;
	/* Global Interrupt Enable */
	GIE = 1;

	init_clcd();
	init_i2c();
	init_ds1307();
	init_timer0();
	init_matrix_keypad();
	init_adc();
	init_i2c_config();

	//clcd_print("  DS1307  TEST  ", LINE1(0));
}

int flag = 0;

void main(void)
{
	init_config();

	/*while (1)
	{
		#if 1
			get_time();
			display_time();
		#else
			get_date();
			display_date();
		#endif
	}*/
	clcd_print("  TIME   EVT SPD", LINE1(0));
	unsigned short adc_reg_val;
	unsigned char key, key1;
	static int z = 1;
	static unsigned char toggle;
	static char *t, *s;
	char e[3];
	//write_external_eeprom(0x01,0);
	//e = read_internal_eeprom(0x01);
	//write_internal_eeprom(0x01, 0x4F);
	//write_internal_eeprom(0x02, 0x4B);
				
		
	//for (int long j = 200000; j--; );
	while (1)
	{
		//--------------------------------------------- FOR POT I.E SPEED VARIATION

		adc_reg_val = read_adc(CHANNEL4) / 10;
		static unsigned short prog_cycle;
		static unsigned short duty_change;
		
		char buff[5];
		//if(duty_change != adc_reg_val)
		//{
		//	duty_change = adc_reg_val;
		//}
		int i = 3;
		do
		{
			buff[i] = (adc_reg_val % 10) + '0';
			adc_reg_val = adc_reg_val / 10;
		} while (i--);
		buff[4] = '\0';
		clcd_print(buff, LINE2(13));

		//------------------------------------------------- FOR TIME FETCH AND DISPLAY

		get_time();
		display_time();

		//-------------------------------------------------- MATRIX KEY READ

		key1 = read_switches(STATE_CHANGE);

		if (key1 != 0xFF)
		{
			key = key1;
			if(key == MK_SW1)
			{
				toggle = !toggle;
			}//for (j = 10000; j--; );
		}

		if ((key == MK_SW1 || key == MK_SW2 || key == MK_SW3 || key == MK_SW4 || key == MK_SW5))
		{
			if(key1 == MK_SW1)
			{
				if(toggle)
				{
					clcd_print(" ON", LINE2(9));
					write_internal_eeprom(0x00, time[0]);
					write_internal_eeprom(0x01, time[1]);
					write_internal_eeprom(0x02, time[2]);
					write_internal_eeprom(0x03, time[3]);
					write_internal_eeprom(0x04, time[4]);
					write_internal_eeprom(0x05, time[5]);
					write_internal_eeprom(0x06, time[6]);
					write_internal_eeprom(0x07, time[7]);
					write_internal_eeprom(0x08, 0x20);
					write_internal_eeprom(0x09, 0x4F);
					write_internal_eeprom(0x10, 0x4E);
					write_internal_eeprom(0x11, buff[0]);
					write_internal_eeprom(0x12, buff[1]);
					write_internal_eeprom(0x13, buff[2]);
					

				}
				else
				{
					clcd_print("OFF", LINE2(9));
					write_internal_eeprom(0x00, time[0]);
					write_internal_eeprom(0x01, time[1]);
					write_internal_eeprom(0x02, time[2]);
					write_internal_eeprom(0x03, time[3]);
					write_internal_eeprom(0x04, time[4]);
					write_internal_eeprom(0x05, time[5]);
					write_internal_eeprom(0x06, time[6]);
					write_internal_eeprom(0x07, time[7]);
					write_internal_eeprom(0x08, 0x4F);
					write_internal_eeprom(0x09, 0x46);
					write_internal_eeprom(0x10, 0x46);
					write_internal_eeprom(0x11, buff[0]);
					write_internal_eeprom(0x12, buff[1]);
					write_internal_eeprom(0x13, buff[2]);
				}
				
			}
			if(key1 == MK_SW2 || key1 == MK_SW3)
			{
				clcd_putch('G', LINE2(10));
				clcd_putch(z + 48, LINE2(11));
				if(key1 == MK_SW2)
				{
					z++;
					if(z == 5)
					{
						z = 1;
					}
				}
				else if(key1 == MK_SW3)
				{
					z--;
					if(z == 0)
					{
						z = 4;
					}
				}
			}
			if(key == MK_SW4)
			{
				CLEAR_DISP_SCREEN;
				//e[0]= read_internal_eeprom(0x01);
				//e[1] = read_internal_eeprom(0x02);
				//e[2] = '\0';
				//clcd_print(e, LINE2(9));
				time[0] = read_internal_eeprom(0x00);
				time[1] = read_internal_eeprom(0x01);
				time[2] = read_internal_eeprom(0x02);
				time[3] = read_internal_eeprom(0x03);
				time[4] = read_internal_eeprom(0x04);
				time[5] = read_internal_eeprom(0x05);
				time[6] = read_internal_eeprom(0x06);
				time[7] = read_internal_eeprom(0x07);
				clcd_putch(read_internal_eeprom(0x08), LINE2(9));
				clcd_putch(read_internal_eeprom(0x09), LINE2(10));
				clcd_putch(read_internal_eeprom(0x10), LINE2(11));
				buff[0] = read_internal_eeprom(0x11);
				buff[1] = read_internal_eeprom(0x12);
				buff[2] = read_internal_eeprom(0x13);

				clcd_print(time, LINE2(0));
				clcd_print(buff, LINE2(13));

			}
		}

		//--------------------------------------------




	}
	
}
