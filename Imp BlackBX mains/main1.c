#include "pic_specific.h"
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"




int flag = 0;

void init_config(void)
{

	/* Clear old content */
	PORTB = 0x00;

	/* Set PORTB as a Output */
	TRISB = 0x00;

	/* Config PORTB as digital */
	ADCON1 = 0x0E;


	/* Global Interrupt Enable */
	GIE = 1;

	init_matrix_keypad();
	init_clcd();
	
	init_timer0();

}



void main(void)
{
	init_config();

	unsigned char key, key1; 
	char ch;
	
	static unsigned char i,j,k,l,m, n,t;
	i = j = k = l = m = n = 48;
	t = 48;
	static int z, q, r, s = 4;
	static unsigned char i1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char j1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char k1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char l1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char m1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char n1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char t1[5];// = (char *) malloc(sizeof(char) * 5);
	static unsigned char toggle;
	CLEAR_DISP_SCREEN;
			//MM:SS:MS
	clcd_print("00:00:00", LINE1(0));
	clcd_print("SW1->Start/Stop", LINE2(0));
	while(1)
	{
		
		//char a[] = "48";

		key1 = read_switches(STATE_CHANGE);

		if (key1 != 0xFF)
		{
			key = key1;
			if(key == MK_SW1)
			{
				toggle = !toggle;
			}//for (j = 10000; j--; );
		}
		//clcd_print()
	//	clcd_print("Enter Password   ", LINE1(0));

		if ((key == MK_SW1 || key == MK_SW2 || key == MK_SW3 || key == MK_SW4))
		{
			if (toggle)
			{
				clcd_print("tap SW2->LAP", LINE1(9));
				if (flag == 1)
				{
					flag = 0;
					i++;
					if(i == 58)
					{
						i = 48;
						t++;
						if(t == 58)
						{
							t = 48;
							k++;
							if(k == 58)
							{
								k = 48;
								l++;
								if(l == 54)
								{
									l = 48;
									//k = 48;
									m++;
									if(m == 58)
									{
										m = 48;
										n++;
										if(n == 58)
										{
											n = 48;
										}
									}
								}
							}
						}	
					}

				}
				clcd_putch(':', LINE1(2));
				clcd_putch(':', LINE1(5));
				clcd_putch(i, LINE1(7));
				clcd_putch(t, LINE1(6));
				clcd_putch(k, LINE1(4));
				clcd_putch(l, LINE1(3));
				clcd_putch(m, LINE1(1));
				clcd_putch(n, LINE1(0));
			}

			if(key1 == MK_SW2 && toggle == 1)
			{
				//CLEAR_DISP_SCREEN;
				clcd_print("LAP", LINE2(0));
				clcd_putch(q + 48,LINE2(3));
				clcd_print(" recorded       ", LINE2(4));
				i1[q] = i;
				j1[q] = j;
				k1[q] = k;
				l1[q] = l;
				m1[q] = m;
				n1[q] = n;
				t1[q] = t;
				q++;
				if(q == 5)
				{
					q = 0;
				}
				//key = MK_SW1;
			}

			if(key == MK_SW3 || key == MK_SW4)
			{
				CLEAR_DISP_SCREEN;
				i = i1[s];
				j = j1[s];
				k = k1[s];
				l = l1[s];
				m = m1[s];
				n = n1[s];
				t = t1[s];
				clcd_putch(':', LINE2(2));
				clcd_putch(':', LINE2(5));
				clcd_putch(i, LINE2(7));
				clcd_putch(t, LINE2(6));
				clcd_putch(k, LINE2(4));
				clcd_putch(l, LINE2(3));
				clcd_putch(m, LINE2(1));
				clcd_putch(n, LINE2(0));
				clcd_putch('<', LINE2(9));
				clcd_putch('-', LINE2(10));
				clcd_print("LAP", LINE2(12));
				clcd_putch(s + 48, LINE2(15));

				if(key1 == MK_SW3)
				{
					s++;
					if(s == 5)
					{
						s = 0;
					}
				}
				else if(key1 == MK_SW4)
				{
					s--;
					if(s == -1)
					{
						s = 4;
					}
				}
				
				toggle = 0;
			}
			//comment the below code out if any problems happen
			if(toggle == 0 && key == MK_SW2)
			{
				CLEAR_DISP_SCREEN;
				clcd_print("LAPS cleared", LINE2(0));
				i1[z] = '0';
				j1[z] = '0';
				k1[z] = '0';
				l1[z] = '0';
				m1[z] = '0';
				n1[z] = '0';
				t1[z] = '0';	
				z++;
				if(z == 5)
				{
					z = 0;
				}
			}
		}
		
		
		RB0 = !RB0;
		for (j = 10000; j--; );
	}
}

