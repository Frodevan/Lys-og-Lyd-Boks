/*
 * lys.c
 *
 * Created: 31.01.2018 18.06.18
 *  Author: medlem
 */ 

#include <avr/io.h>

void setup_lys()
{	
	DDRB |= (1<<PINB0)|(1<<PINB1);
	PORTB &= ~((1<<PINB0)|(1<<PINB1));
}

//
// Skru av/på lys
//
void on_red()
{
	PORTB |= (1<<PINB0);
}

void off_red()
{
	PORTB &= ~(1<<PINB0);
}

void on_green()
{
	PORTB |= (1<<PINB1);
}

void off_green()
{
	PORTB &= ~(1<<PINB1);
}