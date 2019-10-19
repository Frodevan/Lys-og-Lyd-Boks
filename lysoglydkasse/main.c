/*
 * lysoglydkasse.c
 *
 * Created: 28.01.2018 09.57.27
 * Author : medlem
 */ 

#define F_CPU 8000000UL		// Klokkehastighet

//#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "lys.h"
#include "meter.h"
#include "musikk.h"

// Potentiometer = A1 (ikke tilkoblet enda)
// SPI på ISP header (ikke i bruk enda)

int main(void)
{
	//
	// Setup
	//
	setup_lys();
	setup_meter();
	setup_musikk();
	
	//
	// Do stuff
	//
    while (1) 
    {
		for(int i=0; i<10; i++)
		{
			off_red();
			on_green();
			setMeter(rand()%100);
			_delay_ms(500);
			
			on_red();
			off_green();
			setMeter(rand()%100);
			_delay_ms(500);
		}
		restartMusikk();
    }
}


