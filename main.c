/*
 * ATMega16_Timer1_CompareMode.c
 *
 * Created: 2023-06-07 10:23:24 AM
 * Author : a_shi
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

//Clear Timer 1 on Compare Mode "Output Compare A/B Match Interrupt Enable"

void timer1_init(void)
{
	TCCR1B |= (1<<WGM12) | (1<<CS12);		//CTC mode is enabled, Prescaler is set to 256
	TCNT1 = 0;								//Initialize the timer 1.
	OCR1A = 31250;
	
	/*
	Compare Register Count Calculation
	
	Clock Source -> 8MHz external crystal.
	Use Prescaler 256.
	
	Clock freq -> 8000000/256 = 31250Hz
	
	Time period = 1/31250 = 0.000032sec = 0.032millisec
	
	To blink an LED at 1Hz i.e. 1sec = 1000msec (1000msec in 1sec)
	
	To elapse 0.032 milliseconds, it takes 1 count
	So, to elapse 1 milliseconds, it takes 1/0.032count
	So, to elapse 1000 milliseconds, it takes {(1/32)*1000} = 31250 count
	
	*/
	
	TIMSK |= (1<<OCIE1A);		//Timer Counter 1, Output Compare A Match Interrupt Enable.
	sei();						//Global Interrupt Enable.
}

int main(void)
{
	DDRD |= (1<<6);
	timer1_init();
	
    while (1) 
    {
    }
}

ISR (TIMER1_COMPA_vect)
{
	PORTD ^= (1<<6);
}
