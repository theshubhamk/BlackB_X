#include "pic_specific.h"

extern int flag;

void interrupt isr(void)
{
	static unsigned short count;

	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 200)
		{
			count = 0;
			flag = 1;
		}

		TMR0IF = 0;
	}
}
