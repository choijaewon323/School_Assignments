/*
 * 11_week.c
 *
 * Created: 2022-11-08 오후 1:19:03
 * Author : casdf
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

typedef unsigned char uc;

const uc digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
const uc fnd_sel[4] = {0x08, 0x04, 0x02, 0x01};
const uc dot = 0x80;

void printNum(uc num[4]) 
{
	int i;
	for (i = 0; i < 4; i++)
	{
		PORTC = num[i];
		PORTG = fnd_sel[i];
		_delay_ms(2.5);
	}
}

int main(void)
{
    int i, j, k, l;
	uc num[4];
	
	DDRC = 0xff;
	DDRG = 0x0f;
	// PORTC - FND 데이터 신호
	// PORTG - FND 선택 신호
	
	for (i = 0;; i++) 
	{
		if (i == 10) 
		{
			i = 0;
		}
		num[0] = digit[i];
		for (j = 0; j < 10; j++)
		{
			num[1] = digit[j] + dot;
			for (k = 0; k < 10; k++)
			{
				num[2] = digit[k];
				for (l = 0; l < 10; l++)
				{
					num[3] = digit[l];
					printNum(num);
				}
			}
		}
	}
}

