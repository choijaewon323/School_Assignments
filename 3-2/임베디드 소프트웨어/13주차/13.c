#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

typedef unsigned char uc;

#define CDS_VALUE 871

void init_adc();
unsigned short read_adc();
void show_adc(unsigned short value);

const uc digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
const uc fnd_sel[4] = {0x08, 0x04, 0x02, 0x01};
const uc dot = 0x80;
volatile uc led_value;

int main()
{
	unsigned short value;
	DDRA = 0xff;
	DDRC = 0xff;
	DDRG = 0x0f;
	
	led_value = 0b10000000;
	
	init_adc();
	
	while(1)
	{
		value = read_adc();
		show_adc(value);
	}
}

void init_adc()
{
	ADMUX=0x00;
	// 00000000
	// REFS(1:0) = "00" AREF(+5V) 기준전압 사용
	// ADLAR = '0' 디폴트 오른쪽 정렬
	// MUX(4:0) = "00000" ADC0 사용, 단극 입력
	ADCSRA = 0x87;
	// 10000111
	// ADEN = '1' ADC를 Enable
	// ADFR = '0' single conversion 모드
	// ADPS(2:0) = "111" 프리스케일러 128분주
}

unsigned short read_adc()
{
	unsigned char adc_low,adc_high;
	unsigned short value;
	
	ADCSRA |= 0x40; // ADC start conversion, ADSC = '1'
	while((ADCSRA & (0x10)) != 0x10); // ADC 변환 완료 검사
	adc_low=ADCL;
	adc_high=ADCH;
	value = (adc_high <<8) | adc_low;
	
	return value;
}

void show_adc(unsigned short value)
{
	int i;
	uc num[4];
	
	if(value < CDS_VALUE) 
	{
		PORTA=0xff;	
	}
	else PORTA=0x00;
	
	num[3] = (value / 1000) % 10;
	num[2] = (value / 100) % 10;
	num[1] = (value / 10) % 10;
	num[0] = value % 10;
	
	for (i = 0; i < 4; i++)
	{
		PORTC = digit[num[i]];
		PORTG = fnd_sel[3 - i];
		_delay_ms(2.5);
	}
}