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
#include "font.h"

#define _XTAL_FREQ 8000000

uint8_t* theMessage = "Skrrrr ";

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

    uint16_t textLastIndex = strlen(theMessage) - 1;
    while (1) {

        for (uint16_t textIndex = 0; textIndex < textLastIndex; textIndex++) {
            uint8_t currChar = *(theMessage + textIndex) - 32;
            uint8_t nextChar = *(theMessage + textIndex + 1) - 32;

            uint8_t displayData[7]; // rows
            for (uint8_t shifter = 5; shifter < 11; shifter++) {
                // el spin
                for (uint8_t row = 0; row < 7; row++) {
                    displayData[row] = 0;

                    for (uint8_t col = 0; col < shifter; col++) {
                        displayData[row] <<= 1;

                        if (col < 5) {
                            if (font[currChar][col] & (1 << row)) {
                                displayData[row] |= 1;
                            }
                        }

                        if (col > 5) {
                            if (font[nextChar][col - 6] & (1 << row)) {
                                displayData[row] |= 1;
                            }
                        }
                    }
                }

                for (uint8_t del = 0; del < 15; del++) {
                    for (uint8_t i = 0; i < 7; i++) {
                        // set LEDs in row
                        setRow(displayData[i]);

                        // row select
                        switch (i) {
                            case 0:
                                R1 = 0;
                                break;
                            case 1:
                                R2 = 0;
                                break;
                            case 2:
                                R3 = 0;
                                break;
                            case 3:
                                R4 = 0;
                                break;
                            case 4:
                                R5 = 0;
                                break;
                            case 5:
                                R6 = 0;
                                break;
                            case 6:
                                R7 = 0;
                                break;
                        }
                        __delay_ms(1);
                        
                        // select null
                        R1 = R2 = R3 = R4 = R5 = R6 = R7 = 1;
                    }
                }
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