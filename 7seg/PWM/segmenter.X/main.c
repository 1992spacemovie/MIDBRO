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

    uint8_t FaCtr;
    uint8_t SlCtr;
    uint8_t PWM = 20;
    uint8_t temp = 0;
    while (1) {
        if (PWM > FaCtr)
            display(temp);
        else
            display(16);

        if (!FaCtr) {
            SlCtr++;
            SlCtr &= 0b00111111;

            if (SlCtr < 25) {
                PWM = SlCtr << 2;
            } else if (SlCtr > 35) {
                PWM = 255 - (SlCtr << 2);
            } else {
                PWM = 255;
            }

            if (!SlCtr) {
                temp++;
                temp &= 0b00001111;
            }
        }

        FaCtr++;
    }
}

void display(uint8_t num) {
    SEGA = SEGB = SEGC = SEGD = SEGE = SEGF = SEGG = 0;

    if (num > 16)
        return;

    const uint8_t LUT[17] = {
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
        0b00000000
    };

    uint8_t data = LUT[num];

    if (data & (1 << 0))
        SEGA = 1;

    if (data & (1 << 1))
        SEGB = 1;

    if (data & (1 << 2))
        SEGC = 1;

    if (data & (1 << 3))
        SEGD = 1;

    if (data & (1 << 4))
        SEGE = 1;

    if (data & (1 << 5))
        SEGF = 1;

    if (data & (1 << 6))
        SEGG = 1;
}