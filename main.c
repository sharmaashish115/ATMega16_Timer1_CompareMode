/*
 * ATMega16_Timer0.c
 *
 * Created: 2023-06-02 12:06:27 PM
 * Author : a_shi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t count;

int main(void)
{
	DDRD |= (1<<6);
	TCNT0 =0;
	count =0;
	TCCR0 &= ~(1<<CS01);
	TCCR0 |= (1<<CS02) | (1<<CS00);
	TIMSK |= 1<<TOIE0;
	sei();
		
    while (1) 
    {
    }
}

ISR(TIMER0_OVF_vect)
{
	if (count==31)
	{
		PORTD ^= (1<<6);
		count=0;
	}
	else
	count++;
	
}