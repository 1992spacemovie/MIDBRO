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

int main() {

    ADCON0 = 0b00100011; // ADFM=0; VCFG=0; ... ADON=1;
    ADCON1 = 0b01010000; // Fosc/16
    ANSEL = 0b10000000; // ANS7
    ANSELH = 0b00000011; // ANS9; ANS8
    OSCCON = 0b01110101;

    TRISC = 0b11001000;
    TRISB = 0b10000000;
    TRISA = 0b00111011;
    RGB_R = 0;
    RGB_G = 0;
    RGB_B = 0;
    LEDR = 0;
    LEDY = 0;
    LEDG = 0;

    uint8_t rec1[80];
    uint8_t rec2[80];
    uint8_t rec3[80];
    for (uint8_t i = 0; i < 80; i++) {
        rec1[i] = 0;
        rec2[i] = 0;
        rec3[i] = 0;
    }

    while (1) {
        if (BTU) {
            TRISB = 0b11000000;
            LEDR = 1;
            for (uint8_t i = 0; i < 240; i++) {
                uint8_t byte = 0;
                for (uint8_t bit = 0; bit < 8; bit++) {
                    __delay_us(500);
                    byte <<= 1;
                    if (BUZZ)
                        byte |= 0b1;
                }
                if (i < 80)
                    rec1[i] = byte;
                else if (i < 160)
                    rec2[i - 80] = byte;
                else
                    rec3[i - 160] = byte;
            }
            LEDR = 0;
            TRISB = 0b10000000;
            while (BTU) {
                ;
            }
        }

        if (BTL) {
            LEDG = 1;
            for (uint8_t i = 0; i < 240; i++) {
                uint8_t byte;
                if (i < 80)
                    byte = rec1[i];
                else if (i < 160)
                    byte = rec2[i - 80];
                else
                    byte = rec3[i - 160];
                
                for (uint8_t bit = 0; bit < 8; bit++) {
                    __delay_us(500);
                    if (byte & 0b1)
                        BUZZ = 1;
                    else
                        BUZZ = 0;
                    byte >>= 1;
                }
            }
            LEDG = 0;
            while (BTL) {
                ;
            }
        }
    }
}