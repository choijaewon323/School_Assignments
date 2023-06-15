/*
 * 11_week.c
 *
 * Created: 2022-11-08 오후 1:19:03
 * Author : casdf
 */ 

#define START 1
#define STOP 0

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>


typedef unsigned char uc;

const uc digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
const uc fnd_sel[4] = {0x08, 0x04, 0x02, 0x01};
const uc dot = 0x80;

volatile int count = 0;
volatile int signal = STOP;

ISR(INT4_vect)
{
	if (signal == START)
	{
		signal = STOP;
	}
	else
	{
		signal = START;
	}
	_delay_ms(10);
}

ISR(INT5_vect)
{
	if (signal == STOP)
	{
		count = 0;
	}
	_delay_ms(10);
}

void display_fnd(int c)
{
	int i, fnd[4];
	fnd[3] = (c / 1000) % 10;	// 천
	fnd[2] = (c / 100) % 10;	// 백
	fnd[1] = (c / 10) % 10;		// 십
	fnd[0] = c % 10;			// 일
	for (i = 0; i < 4; i++)
	{
		PORTC = digit[fnd[i]];
		PORTG = fnd_sel[3 - i];
		_delay_ms(2.5);
	}
}

int main(void)
{
	DDRC = 0xff;
	DDRG = 0x0f;
	DDRE = 0x00;
	EICRB = 0x0a;
	EIMSK = 0x30;
	sei();
	
	// PORTC - FND 데이터 신호
	// PORTG - FND 선택 신호
	
	while (1) 
	{
		display_fnd(count);
		
		if (signal == START)
		{
			count = (count + 1) % 10000;	// 0000 ~ 9999
		}
	}
}

