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

void LCDSend(uint8_t data, uint8_t isData);
void LCDInit();
void LCDSetCur(uint8_t h, uint8_t w);
void LCDSendStr(uint8_t* s);

int main() {
    ADCON0 = 0b00100011; // ADFM=0; VCFG=0; ... ADON=1;
    ADCON1 = 0b01010000; // Fosc/16
    ANSEL = 0b00000000; // ANS7
    ANSELH = 0b00000000; // ANS9; ANS8
    OSCCON = 0b01110101;

    TRISC = 0b00000000;
    TRISB = 0b10101111;
    TRISA = 0b11101000;

    LEDR = 0;
    BUZZ = 0;
    LCDRS = 0;
    LCDRW = 0;
    LCDE = 0;

    LCDInit();

    LCDSendStr("Napeti:");

    uint8_t a = ' ';
    while (1) {
        LCDSetCur(1, 1);
        LCDSend(a, 1);
        a++;
        if (a == 127)
            a = ' ';
        __delay_ms(10);
    }
}

void LCDInit() {
    __delay_ms(20); // wait for LCD
    LCDSend(0b00111000, 0);
    LCDSend(0b00001000, 0);
    LCDSend(0b00000001, 0);
    __delay_ms(15); // clear
    LCDSend(0b00000110, 0);
    LCDSend(0b00001100, 0);
}

void LCDSetCur(uint8_t h, uint8_t w) {
    LCDSend(0b10000000 + h + w * 64, 0);
}

void LCDSendStr(uint8_t* s) {
    uint8_t ch;
    do {
        ch = *s;
        if (ch)
            LCDSend(ch, 1);
        s++;
    } while (ch);
}

void LCDSend(uint8_t data, uint8_t isData) {

    LCDRS = isData;
    LCDE = 1;

    LCDD0 = LCDD1 = LCDD2 = LCDD3 = LCDD4 = LCDD5 = LCDD6 = LCDD7 = 0;

    if (data & (1 << 0))
        LCDD0 = 1;

    if (data & (1 << 1))
        LCDD1 = 1;

    if (data & (1 << 2))
        LCDD2 = 1;

    if (data & (1 << 3))
        LCDD3 = 1;

    if (data & (1 << 4))
        LCDD4 = 1;

    if (data & (1 << 5))
        LCDD5 = 1;

    if (data & (1 << 6))
        LCDD6 = 1;

    if (data & (1 << 7))
        LCDD7 = 1;

    LCDE = 0;
}