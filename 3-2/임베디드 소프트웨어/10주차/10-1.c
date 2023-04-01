#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
    unsigned char value;
	int i;
	DDRA = 0xff;
	for (;;)
	{
		value = 128;
		PORTA = value;
		_delay_ms(200);
		for (i = 0; i < 7; i++)
		{
			value >>= 1;
			PORTA = value;
			_delay_ms(200);
		}
		
		for (i = 0; i < 7; i++)
		{
			value <<= 1;
			PORTA = value;
			_delay_ms(200);
		}
	}
}

