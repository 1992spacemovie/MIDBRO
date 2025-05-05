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

typedef unsigned char UINT8;
typedef unsigned short UINT16;

void main() {
	ADCON0 = ADCON1 = 0;	// PIC init
	ANSEL = ANSELH = 0;
	OSCCON = 0b1110101;

	TRISC = 0b11001000;		// port init
	TRISB = 0b10000000;
	TRISA = 0b00111011;
	BUZZ = 0;
	RGB_R = 0;
	RGB_G = 0;
	RGB_B = 0;
	LEDR = 0;
	LEDY = 0;
	LEDG = 0;

	UINT8 R = 127;			// initial RGB LED values
	UINT8 G = 0;
	UINT8 B = 0;
	UINT8 HueR = 255;
	UINT8 HueG = 1;
	UINT8 HueB = 0;
	UINT8 Saturation = 0;	// reversed (0 = full, 255 = white)
	UINT8 Value = 255;
	UINT8 HalfValue;
	UINT8 PWMCtr;
	UINT8 SettingState = 0;

	while (1) {

		// PWM generator loop
		if (R > PWMCtr)
			RGB_R = 1;
		else
			RGB_R = 0;

		if (G > PWMCtr)
			RGB_G = 1;
		else
			RGB_G = 0;

		if (B > PWMCtr)
			RGB_B = 1;
		else
			RGB_B = 0;

		PWMCtr++;

		// do stuff at the start of the PWM cycle
		if (!PWMCtr) {
			if (BTL) {
				if (SettingState == 1) {
					// hue generator

					// 255 | RRRRRRRRRRBBBBBBBBBBGGGGGGGGGG                         
					//     | G        BR        GB        R                         
					//     |  G      B  R      G  B      R                          
					//     |   G    B    R    G    B    R                           
					//     |    G  B      R  G      B  R                            
					//   0 |     GB        RG        BR                             


					if (HueR) {					// if red nonzero
						if (HueB == 255) {
							HueR--;				// decrease if blue full
							if (!HueR)
								HueG++;			// start green when reached zero
						} else if (HueR != 255)	// or continue increasing red
							HueR++;
					}

					if (HueB) {					// if blue nonzero
						if (HueG == 255) {
							HueB--;				// decrease if green full
							if (!HueB)
								HueR++;			// start red when reached zero
						} else if (HueB != 255) // or continue increasing blue
							HueB++;
					}

					if (HueG) {					// if green nonzero
						if (HueR == 255) {
							HueG--;				// decrease if red full
							if (!HueG)
								HueB++;			// start blue when reached zero
						} else if (HueG != 255) // or continue increasing green
							HueG++;
					}
				}
				if (SettingState == 2) {
					// saturation setting
					Saturation++;
				}
				if (SettingState == 3) {
					// value setting
					Value--;
				}

				R = HueR + Saturation; // add saturation to hue
				G = HueG + Saturation;
				B = HueB + Saturation;

				if (R < Saturation) // overflow fixes
					R = 255;
				if (G < Saturation)
					G = 255;
				if (B < Saturation)
					B = 255;

				HalfValue = Value >> 1;		// deal with value,
				R = (R * HalfValue) >> 8;	// using value/2 for better linearity
				G = (G * HalfValue) >> 8;	// multiplies by value/2, then divides
				B = (B * HalfValue) >> 8;	// by 256
			}

			if (BTU) {
				// current mode selector
				if (SettingState > 3)	// don't care if still pressed
					continue;

				SettingState++;
				if (SettingState > 3)	// wrap around
					SettingState = 0;

				LEDR = (SettingState == 1);	// hue
				LEDY = (SettingState == 2);	// saturation
				LEDG = (SettingState == 3);	// value

				SettingState |= 0b10000000;	// flag as pressed
			} else
				SettingState &= 0b11;		// unflag when released
		}

		__delay_us(1);
	}
}

