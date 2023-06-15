#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define DO	17
#define RE	43
#define MI	66
#define FA	77
#define SOL 96
#define LA	113
#define TI	130
#define UDO	136

#define ON	1
#define OFF 0

volatile state;
volatile index;

volatile int melody[8] = {DO, RE, MI, FA, SOL, LA, TI, UDO};

ISR(TIMER0_OVF_vect)
{
	if (state == ON)
	{
		PORTB = 0x00;
		state = OFF;
	}
	else
	{
		PORTB = 0x10;
		state = ON;
	}
	TCNT0 = melody[index];
}

ISR(INT5_vect)
{
	index = (index + 1) % 8;
	_delay_ms(10);
}

int main(void)
{
	// 스위치
	DDRE = 0x00;
	EICRB = 0x08;
	EIMSK = 0x20;
	sei();
	
	// 타이머
	DDRB = 0x10;
	TCCR0 = 0x03;
	TIMSK = 0x01;
	
	state = ON;
	index = 0;
	
    while (1) 
    {
		
    }
}

