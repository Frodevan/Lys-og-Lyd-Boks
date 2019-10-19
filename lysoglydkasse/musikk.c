/*
 * CFile1.c
 *
 * Created: 30.01.2018 01.03.50
 *  Author: medlem
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "tone.h"

void playertikk();

//
// Format:
//    Tone			= Semitone (0-11), Oktav (0-9), Lengde (0-255)
//    Pause			= 0x80, Lengde (0x255)
//    Melodi Slutt	= 0xFF
//
//   Alle lengder er i antall 60Hz tikk.
//
const uint8_t melodi[] = {
	7, 4, 20,
	0, 5, 20,
	4, 5, 20,
	
	7, 5, 10,
	0x80, 10,
	0x80, 10,
	7, 5, 5,
	0x80, 5,
	7, 5, 10,
	0x80, 10,
	
	4, 5, 10,
	0x80, 10,
	7, 5, 10,
	0x80, 10,
	4, 5, 10,
	0x80, 10,
	
	0, 5, 10,
	0x80, 10,
	4, 5, 10,
	0x80, 10,
	0, 5, 10,
	0x80, 10,
	
	7, 4, 40,
	0x80, 20,
	
	7, 4, 20,
	0, 5, 20,
	4, 5, 20,
		
	7, 5, 10,
	0x80, 10,
	0x80, 10,
	7, 5, 5,
	0x80, 5,
	7, 5, 10,
	0x80, 10,
		
	4, 5, 10,
	0x80, 10,
	4, 5, 10,
	0x80, 10,
	4, 5, 10,
	0x80, 10,
	
	7, 4, 10,
	0x80, 10,
	7, 4, 10,
	0x80, 10,
	7, 4, 10,
	0x80, 10,
	
	0, 5, 60,
	0xFF};

volatile uint8_t playerstep;
volatile uint8_t playing;

volatile uint16_t ptr;
volatile uint16_t cnt;
volatile uint8_t wit;

void setup_musikk()
{
	setup_lyd();
	cli();
	TCCR0A |= (1<<WGM00) | (1<<WGM01);	// Fast PWM
	TCCR0B |= (1<<CS01) | (1<<CS00);	// Clock Source
	TCCR0B &= ~((1<<WGM02) | (1<<FOC0A) | (1<<FOC0B) | (1<<CS02));
	TIMSK0 |= (1<<TOV0);				// Enable Imterrupts
	playerstep = 0;
	playing = 0;
	sei();
}


ISR(TIM0_OVF_vect)  // Trigges ~240Hz
{
	sei();
	if(!((playerstep++)&0x03))
	{
		playertikk();
	}
	
}

//
// Starter spilleren fra starten av melodi
//
void restartMusikk()
{
	cli();
	ptr = 0;
	cnt = 0;
	wit = 0;
	playing = 0xFF;
	sei();
}

void playertikk()  // Kalles hver ~60Hz
{
	while(playing & (cnt++ >= wit))		// Spiller vi? Er vi klar til neste event?
	{
		if(melodi[ptr] == 0x80)			// tolk og utfør event
		{
			stopTone();
			ptr++;
		}
		else if(melodi[ptr] == 0xFF)
		{
			stopTone();
			playing = 0;
			break;
		}
		else
		{
			playTone(melodi[ptr], melodi[ptr+1]);
			ptr = ptr+2;
		}
		wit = melodi[ptr++];		// Ferdig utført, pek videre til neste event
		cnt = 0;
	}
}