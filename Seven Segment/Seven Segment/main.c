/*
 * 7seg.c
 *
 * Created: 3/21/2016 2:05:48 PM
 * Author : user
 Description: the code implements functions to prent numbers on seven segment displays connected to single port PORTC
              PORTD0 and PORTD1 are used as control pins
			  Timer0 is implemented to print the number for some time inorder to nullify the blinking effect.
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char seg_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//7 seg display code
unsigned char c=0;                                                           // a count variable

ISR(TIMER0_OVF_vect)   // timer0 isr
{
c++;
PORTB=0xFF;
}

void timer_init()          //timer0 initialisation with prescalar 1024
{
TCCR0|=(1<<CS02)|(1<<CS00);
TIMSK|=(1<<TOIE0);	
}

void display(unsigned char digit)     //function to display single digit
{

PORTC=seg_code[digit];
_delay_ms(5);	
}

void display_2digit(unsigned char data)          //funtion to display a two digit number
{
 unsigned char i=0,j,a;
 a=0x01;
 while(i<2)
 {
	 j=data%10;
	 data=data/10;
	 PORTD=a;
	 PORTC=seg_code[j];
	 _delay_ms(17.5);
	 a=a<<1;
	 i++;
 }
}

/* main function runs the code to count from 00 to 99 */
int main(void)
{
	char i;
	DDRC=0xFF;
	DDRD=0xFF; 
	DDRB=0xFF;
	PORTC=0x00;
	PORTB=0x00;
	timer_init();
	sei();
	while(1)
	{
	for(i=0;i<99;i++)    //code for counting
	{  
		c=0;
		TCNT0=0;
		while(c<=20)
		{
		display_2digit(i);
		}
		
	}
}
}

