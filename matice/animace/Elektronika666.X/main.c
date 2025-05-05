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
#include <string.h>
#include "pin_def.h"

#define _XTAL_FREQ 8000000

void setRow(uint8_t data);

void main() {
    ADCON0 = 0b00100011; // ADFM=0; VCFG=0; ... ADON=1;
    ADCON1 = 0b01010000; // Fosc/16
    ANSEL = 0b00000000; // ANS7
    ANSELH = 0b00000000; // ANS9; ANS8
    OSCCON = 0b01110101;

    TRISA = 0b11111111;
    TRISB = 0b00001111;
    TRISC = 0b00000000;

    uint8_t displayData[5];

    for (uint8_t i = 0; i < 5; i++) {
        displayData[i] = 0;
    }

    uint8_t state = 4;
    int8_t adder = 0;

    while (1) {

        // shift data
        for (uint8_t i = 4; i; i--) {
            displayData[i] = displayData[i - 1];
        }

        // new data
        //        if (BTU) {
        //            if (adder == 1)
        //                adder = -1;
        //            else
        //                adder = 1;
        //        }
        if (BTU)
            adder = 1;
        if (BTL)
            adder = -1;



        state += adder;

        if (state == 255)
            state = 0;

        if (state > 9)
            state = 8;

        displayData[0] = (1 << state) - 1;

        uint8_t rowData[7]; // rows
        // el spin
        for (uint8_t row = 0; row < 7; row++) {
            rowData[row] = 0;

            for (uint8_t col = 0; col < 5; col++) {
                rowData[row] <<= 1;

                if (displayData[col] & (1 << row)) {
                    rowData[row] |= 1;
                }
            }
        }

        for (uint8_t del = 0; del < 20; del++) {
            for (uint8_t i = 0; i < 7; i++) {
                // set LEDs in row
                setRow(rowData[i]);

                // row select
                switch (i) {
                    case 0:
                        R7 = 0;
                        break;
                    case 1:
                        R6 = 0;
                        break;
                    case 2:
                        R5 = 0;
                        break;
                    case 3:
                        R4 = 0;
                        break;
                    case 4:
                        R3 = 0;
                        break;
                    case 5:
                        R2 = 0;
                        break;
                    case 6:
                        R1 = 0;
                        break;
                }
                __delay_ms(1);

                // select null
                R1 = R2 = R3 = R4 = R5 = R6 = R7 = 1;
            }
        }
    }
}

void setRow(uint8_t data) {
    if (data & (1 << 4))
        C1 = 1;
    else
        C1 = 0;

    if (data & (1 << 3))
        C2 = 1;
    else
        C2 = 0;

    if (data & (1 << 2))
        C3 = 1;
    else
        C3 = 0;

    if (data & (1 << 1))
        C4 = 1;
    else
        C4 = 0;

    if (data & (1 << 0))
        C5 = 1;
    else
        C5 = 0;
}