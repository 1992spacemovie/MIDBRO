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

UINT8 BuzzSts;

int main() {

    ADCON0 = 0b00100011; // ADFM=0; VCFG=0; ... ADON=1;
    ADCON1 = 0b01010000; // Fosc/16
    ANSEL = 0b10000000; // ANS7
    ANSELH = 0b00000011; // ANS9; ANS8
    OSCCON = 0b01110101;

    TRISC = 0b11001000;
    TRISB = 0b11000000;
    TRISA = 0b00111011;
    RGB_R = 0;
    RGB_G = 0;
    RGB_B = 0;
    LEDR = 0;
    LEDY = 0;
    LEDG = 0;

    BuzzSts = BUZZ;
    
    while (1) {
        if(BUZZ != BuzzSts){
            LEDR = 1;
            BuzzSts = BUZZ;
        }
        if(BTU){
            LEDR = 0;
            BuzzSts = BUZZ;
            __delay_ms(1000);
        }
    }
}