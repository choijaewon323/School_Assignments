#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
    unsigned char value;
	DDRA = 0xff;
	for (;;)
	{
		value = 128;	// 도
		PORTA = value;
		_delay_ms(333);
		
		value >>= 2;	// 미
		PORTA = value;
		_delay_ms(333);
		
		value >>= 2;	// 솔
		PORTA = value;
		_delay_ms(333);
		
		value = 128;	// 도
		PORTA = value;
		_delay_ms(333);
		
		value >>= 2;	// 미
		PORTA = value;
		_delay_ms(333);
		
		value >>= 2;	// 솔
		PORTA = value;
		_delay_ms(333);
		
		value >>= 1;	// 라
		PORTA = value;
		_delay_ms(333);
		
		PORTA = value;	// 라
		_delay_ms(333);
		
		PORTA = value;	// 라
		_delay_ms(333);
		
		value <<= 1;	// 솔
		PORTA = value;
		_delay_ms(999);
		
		value <<= 1;	// 파
		PORTA = value;
		_delay_ms(333);
		
		PORTA = value;	// 파
		_delay_ms(333);
		
		PORTA = value;	// 파
		_delay_ms(333);
		
		value <<= 1;	// 미
		PORTA = value;
		_delay_ms(333);
		
		PORTA = value;	// 미
		_delay_ms(333);
		
		PORTA = value;	// 미
		_delay_ms(333);
		
		value <<= 1;	// 레
		PORTA = value;
		_delay_ms(333);
		
		PORTA = value;	// 레
		_delay_ms(333);
		
		PORTA = value;	// 레
		_delay_ms(333);
		
		value <<= 1;	// 도
		PORTA = value;
		_delay_ms(999);
	}
}

