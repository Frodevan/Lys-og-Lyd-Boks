/*
 * meter.c
 *
 * Created: 30.01.2018 01.20.02
 *  Author: medlem
 */ 

#include <avr/io.h>

void setup_meter()
{
	DDRB |= (1<<PINB2);		// Meter pin
	TCCR0A |= (1<<COM0A1) | (1<<COM0A0) | (1<<WGM00) | (1<<WGM01);	// Pin mode, Fast PWM
	TCCR0B |= (1<<CS01) | (1<<CS00);								// Clock Source
	TCCR0B &= ~((1<<WGM02) | (1<<FOC0A) | (1<<FOC0B) | (1<<CS02));
}

//
// Flytt nåla til posisjon (0-100)
//
void setMeter(uint16_t x)
{
	OCR0A = x*255/100;
}
