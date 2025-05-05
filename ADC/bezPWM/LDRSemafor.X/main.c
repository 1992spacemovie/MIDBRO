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

void ADConv(void);

UINT8 TRIM;
UINT8 LDR;

void main(void) {
    start:
    OSCCON = 0b01110101;
    ADCON0 = 0b00000001; // ADFM=0; VCFG=0; ... ADON=1;
    ADCON1 = 0b01010000; // Fosc/16
    ANSEL = 0b10000000; // ANS7
    ANSELH = 0b00000011; // ANS9; ANS8

    TRISC = 0b11001000;
    TRISB = 0b10000000;
    TRISA = 0b00111011;

    BUZZ = 0;
    RGB_R = 0;
    RGB_G = 0;
    RGB_B = 0;
    LEDR = 0;
    LEDY = 0;
    LEDG = 0;

    char delayCount = 0;
    char state = 0;
    char tickCount = 0;
    char targetTickCount = 20;
    unsigned char timer = 0;

    while (!BTU) {
        ADConv();
        timer++;
        __delay_ms(1);
        if ((LDR < TRIM) && (timer & 0b11000000)) {
            RGB_R = 1;
            RGB_G = 1;
            RGB_B = 1;
        } else {
            RGB_R = 0;
            RGB_G = 0;
            RGB_B = 0;
        }
    }
    RGB_R = 0;
    RGB_G = 0;
    RGB_B = 0;

    while (1) {
        switch (state) {
            case 0:
                LEDR = 1; //vse cervena
                RGB_R = 1;
                delayCount = 10;
                break;

            case 1:
                LEDY = 1; //zluta
                delayCount = 10;
                break;

            case 2:
                LEDR = 0; //zelena
                LEDY = 0;
                LEDG = 1;
                delayCount = 30;
                break;

            case 3:
                LEDG = 0; //zluta
                LEDY = 1;
                delayCount = 10;
                break;

            case 4:
                LEDY = 0; //cervena
                LEDR = 1;
                delayCount = 10;
                break;

            case 5:
                RGB_R = 0; //zelena pro chodce
                RGB_G = 1;
                delayCount = 20;
                targetTickCount = 1;
                break;

            case 6:
                RGB_R = 1; //cervena pro chodce
                RGB_G = 0;
                delayCount = 10;
                targetTickCount = 20;
                break;
        }

        for (char i = 0; i < delayCount; i++) { //centralni cekací smycka
            __delay_ms(50);
            tickCount++;
            if (tickCount > targetTickCount) {
                tickCount = 0;
                BUZZ = 1; // tick
                __delay_ms(3);
                BUZZ = 0;
            }
            if (BTL) {
                goto start;
            }
        }

        state++;
        if (state > 6) {
            state = 0;
            delayCount = 0;
            LEDR = 0;
            RGB_R = 0;

            while (1) {
                LEDY = 0;

                ADConv();

                if (LDR < TRIM) {
                    break;
                }

                if (delayCount < 10) {
                    LEDY = 1;
                } else {
                    LEDY = 0;
                    if (delayCount == 20) {
                        delayCount = 0;
                    }
                }

                delayCount++;
                __delay_ms(100);
            }

        }
    }
}

void ADConv() {
    // adc prevody
    ADCON0 = 0b00100111;
    while (ADCON0 & 0b00000010) {
    }
    TRIM = ADRESH;
    ADCON0 = 0b00100011;
    while (ADCON0 & 0b00000010) {
    }
    LDR = ADRESH;
}