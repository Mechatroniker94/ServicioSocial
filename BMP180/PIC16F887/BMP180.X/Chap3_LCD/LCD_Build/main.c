/*
 *	LCD interface example
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, with
 *	the hardware connected as follows (the standard 14 pin 
 *	LCD connector is used):
 *	
 *	PORTC bits 0-3 are connected to the LCD data bits 4-7 (high nibble)
 *	PORTA bit 2 is connected to the LCD RS input (register select)
 *  RW input (read/write) connected to ground
 *	PORTA bit 1 is connected to the LCD EN bit (enable)
 *	
 *	To use these routines, set up the port I/O (TRISA, TRISD) then
 *	call lcd_init(), then other routines as required.
 *	
 */
#define _LEGACY_HEADERS //Added for compiler versions 9.81+
#include <htc.h>
#include "lcd.h"

void pause( unsigned short usvalue );		//Establish pause routine function

__CONFIG (INTIO & WDTDIS & MCLRDIS & UNPROTECT);

#define number 0x30

unsigned char b0;

void
main(void)
{
ANSEL = 0;		// Set PORTA all Digital
ANSELH = 0;
CM1CON0 = 0;	// Comparator 1 off
CM2CON0 = 0;	// Comparator 2 off

TRISA = 0;		// All PORTA Outputs
TRISC = 0;		// All PORTC Outputs

lcd_init();		// Initialize LCD Display

while (1==1)
	{
	lcd_clear();				// Clear LCD screen
	lcd_goto(0);				// select first line
//	lcd_puts("Beginners Guide");	// Display Hello World
	for (b0=0; b0<10; b0=b0+1)	// Create counting loop
		{
		lcd_putch(b0+number);	// Display count on LCD
		pause (250);			// Delay 250 msec to see count
		}
	lcd_goto(0x40);				// Select second line
//	lcd_puts("    Volume 2");	// Display Hello World
	lcd_puts("Hello World");	// Display Hello World
	pause (1000);				// Delay for 1 second to read display
	}
	
}
