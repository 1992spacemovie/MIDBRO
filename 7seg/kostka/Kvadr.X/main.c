#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#include <xc.h>
#include "pin_def.h"

#define _XTAL_FREQ 8000000

/*typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned short uint16_t;*/

void display(uint8_t num);

void main() {
	ADCON0 = 0b00100011; // ADFM=0; VCFG=0; ... ADON=1;
	ADCON1 = 0b01010000; // Fosc/16
	ANSEL = 0b10000000; // ANS7
	ANSELH = 0b00000011; // ANS9; ANS8
	OSCCON = 0b01110101;

	TRISC = 0b11001000;
	TRISB = 0b11101111;
	TRISA = 0b11111011;


	// range select
	uint8_t range = 2;
	while (!BTU) {
		display(range);
		if (BTL) {
			range++;
			if (range > 15)
				range = 2;

			while (BTL) {
				__delay_ms(10); // debounce frfr
			}
		}
	}

	// "game" loop
	uint8_t randomness;
	uint8_t ctr;
	uint8_t PWM;
	int8_t PWMAdder = 4;
	while (1) {
		if (BTU) {
			// random number gen
			randomness++;
			if(randomness > range)
				randomness = 1;
			
			// animation
			ctr++;
			if(PWM > ctr)
				display(17);
			else
				display(16); // display off
			
			if(!ctr){
				// fade
				PWM += PWMAdder;
				if(PWM > 100)
					PWMAdder = -5;
				if(PWM < 5)
					PWMAdder = 5;
			}
			
		} else {
			display(randomness);
            PWM = 5;
		}
	}
}

void display(uint8_t num) {

	if (num > 17)
		return;

	const uint8_t LUT[18] = {
		0b00111111,
		0b00000110,
		0b01011011,
		0b01001111,
		0b01100110,
		0b01101101,
		0b01111101,
		0b00000111,
		0b01111111,
		0b01101111,
		0b01110111,
		0b01111100,
		0b00111001,
		0b01011110,
		0b01111001,
		0b01110001,
		0b00000000,
        0b01110110
	};

	uint8_t data = LUT[num];

	if (data & (1 << 0))
		SEGA = 1;
	else
		SEGA = 0;

	if (data & (1 << 1))
		SEGB = 1;
	else
		SEGB = 0;

	if (data & (1 << 2))
		SEGC = 1;
	else
		SEGC = 0;

	if (data & (1 << 3))
		SEGD = 1;
	else
		SEGD = 0;

	if (data & (1 << 4))
		SEGE = 1;
	else
		SEGE = 0;

	if (data & (1 << 5))
		SEGF = 1;
	else
		SEGF = 0;

	if (data & (1 << 6))
		SEGG = 1;
	else
		SEGG = 0;
}