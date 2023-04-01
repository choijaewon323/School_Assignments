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
volatile int song[32] = {MI, RE, DO, RE, MI, MI, MI, MI, 
	RE, RE, RE, RE, MI, SOL, SOL, SOL, 
	MI, RE, DO, RE, MI, MI, MI, MI, 
	RE, RE, MI, RE, DO, DO, DO, DO};

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
	TCNT0 = song[index];
}

int main(void)
{
	// 타이머
	DDRB = 0x10;
	TCCR0 = 0x03;
	TIMSK = 0x01;
	sei();
	
	state = ON;
	index = 0;
	
    while (1) 
    {
		_delay_ms(500);
		index = (index + 1) % 32;
    }
}

