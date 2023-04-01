/*
 * 11_week.c
 *
 * Created: 2022-11-08 오후 1:19:03
 * Author : casdf
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>

typedef unsigned char uc;

const uc digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
const uc fnd_sel[4] = {0x08, 0x04, 0x02, 0x01};
const uc dot = 0x80;

int main(void)
{
	int number;
	DDRA = 0xff;
	DDRC = 0xff;
	DDRG = 0x0f;
	// PORTC - FND 데이터 신호
	// PORTG - FND 선택 신호
	// PORTA - LED 원하는 값 출력
	PORTG = fnd_sel[3];
	
	while (1)
	{
		number = rand() % 8;
		PORTC = digit[number];
		PORTA = (0x01 << number);
		_delay_ms(1000);
	}
}

