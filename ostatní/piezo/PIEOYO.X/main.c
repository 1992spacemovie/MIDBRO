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
#include "notes.h"

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

void tone(UINT8 T, UINT16 t);
//void note(UINT8 T, UINT8 T);

UINT8 TR1;
UINT8 TR2;
UINT8 TR3;
UINT8 Shifter;
UINT8 ctr;
UINT8 SloCtr;

UINT8 notes[] = {C4, D4, E4, F4, G4, A4, B4, C5};


UINT8 MDur[] = {
    //RR
    //90, 90, 60, 90, 90, 15, 15, 30, 90, 90, 120, 15, 15, 15, 30, 15, 90, 90, 60, 90, 90, 15, 15, 30, 90, 90, 120, 15, 15, 15, 30, 15, 60, 30, 30, 30, 30, 30, 45, 15, 120, 60

    //Nokia
    //30,30,60,60,30,30,60,60,30,30,60,60,120

    //Doom
    //23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,135,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,135,23,23,23,23,23,23,23,23

    //GRSL
    //36,73,36,54,18,36,73,36,54,18,36,73,36,54,18,36,73,36,73,36,73,36,54,18,36,73,36,54,18,36,54,18,36,54,18,36,219,146,18,36,73,36,54,18,36,73,36,54,18,36,73,36,73,146,18,36,73,36,54,18,36,54,18,36,54,18,36

    //IMP
    //87,87,14,14,14,14,29,29,87,87,14,14,14,14,29,29,58,58,58,43,14,58,43,14,116,58,58,58,43,14,58,43,14,116,58,43,14,58,43,14,14,14,29,29,29,58,43,14,14,14,14,29,29,58,43,21,58,43,14,116,58,43,14,58,43,14,14,14,29,29,29,58,43,14,14,14

    //TET
    44,22,22,44,22,22,44,22,22,44,22,22,66,22,44,44,44,44,22,44,22,22,66,22,44,22,22,66,22,44,22,22,44,22,22,44,44,44,44,44,44,22,22,44,22,22,44,22,22,44

    //KEYC
    //37,37,37,37,37,37,18,56,37,37,18,56,18,37,37,37,18,37,37,37,37,37,37,18,56,37,37,37,37,37,37,18,56,37,37,37,37,37,37,18,56,37,225

    //TAK
    //18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18
    
    //KOL
    //29,29,29,59,88,59,59,59,59,59,29,59,59,59,59,59,29,59,59,59,59,118,29,59,59,59,59
};

UINT8 MNot[] = {
    //RR
    //D5, E5, A4, E5, FS5, A5, G5, FS5, D5, E5, A4, A4, A4, B4, D5, D5, D5, E5, A4, E5, FS5, A5, G5, FS5, D5, E5, A4, A4, A4, B4, D5, D5, 0, B4, CS5, D5, D5, E5, CS5, B4, A4, 0

    //Nokia
    //E5,D5,FS4,GS4,CS5,B4,D4,E4,B4,A4,CS4,E4,A4

    //Doom
    //E2,E2,E3,E2,E2,D3,E2,E2,C3,E2,E2,AS2,E2,E2,B2,C3,E2,E2,E3,E2,E2,D3,E2,E2,C3,E2,E2,AS2,E2,E2,E3,E2,E2,D3,E2,E2,C3,E2,E2,AS2,E2,E2,B2,C3,E2,E2,E3,E2,E2,D3,E2,E2,C3,E2,E2,AS2,E2,E2,E3,E2,E2,D3,E2,E2

    //GRSL
    //G4,AS4,C5,D5,DS5,D5,C5,A4,F4,G4,A4,AS4,G4,G4,FS4,G4,A4,FS4,D4,G4,AS4,C5,D5,DS5,D5,C5,A4,F4,G4,A4,AS4,A4,G4,FS4,E4,FS4,G4,F5,E5,D5,C5,A4,F4,G4,A4,AS4,G4,G4,FS4,G4,A4,FS4,D4,F5,E5,D5,C5,A4,F4,G4,A4,AS4,A4,G4,FS4,E4,FS4,G4

    //IMP
    //A4,A4,A4,A4,A4,A4,F4,0,A4,A4,A4,A4,A4,A4,F4,0,A4,A4,A4,F4,C5,A4,F4,C5,A4,E5,E5,E5,F5,C5,A4,F4,C5,A4,A5,A4,A4,A5,GS5,G5,DS5,D5,DS5,0,A4,DS5,D5,CS5,C5,B4,C5,0,F4,GS4,F4,A4,C5,A4,C5,E5,A5,A4,A4,A5,GS5,G5,DS5,D5,DS5,0,A4,DS5,D5,CS5,C5,B4

    //TET
    E5,B4,C5,D5,C5,B4,A4,A4,C5,E5,D5,C5,B4,C5,D5,E5,C5,A4,A4,A4,B4,C5,D5,F5,A5,G5,F5,E5,C5,E5,D5,C5,B4,B4,C5,D5,E5,C5,A4,A4,0,E5,B4,C5,D5,C5,B4,A4,A4,C5

    //KEYC
    //C4,E4,G4,E4,C4,E4,G4,E4,A3,C4,E4,C4,A3,C4,E4,C4,G3,B3,D4,B3,G3,B3,D4,B3,G3,G3,G3,G3,G3,G3,G3,G3,G3,C4,E4,G4,E4,C4,E4,G4,E4,A3,C4,E4,C4,A3,C4,E4,C4,G3,B3,D4,B3,G3,B3,D4,B3,G3

    //TAK
    //FS5,FS5,D5,B4,0,B4,0,E5,0,E5,0,E5,GS5,GS5,A5,B5,A5,A5,A5,E5,0,D5,0,FS5,0,FS5,0,FS5,E5,E5,FS5,E5,FS5,FS5,D5,B4,0,B4,0,E5,0,E5,0,E5,GS5,GS5,A5,B5,A5,A5
            
    //KOL
    //E5,F5,0,C5,A4,C5,D5,F5,E5,B4,0,D5,D5,D5,C5,C5,0,G4,G4,A4,A4,A4,0,C5,C5,D5,D5
};

int main() {
    ADCON0 = ADCON1 = 0;
    ANSEL = ANSELH = 0;
    OSCCON = 0b1110101;

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

    Shifter = 1;
    TR1 = TR2 = TR2 = 0;

    while (1) {
        if (TR1 <= ctr) {
            LEDR = 0;
        } else {
            LEDR = 1;
        }

        if (TR2 <= ctr) {
            LEDY = 0;
        } else {
            LEDY = 1;
        }

        if (TR3 <= ctr) {
            LEDG = 0;
        } else {
            LEDG = 1;
        }

        if (!(ctr & 0b00111111)) {
            if ((Shifter & 0b1) || (Shifter & 0b10000))
                TR1++;
            else
                if (TR1)
                TR1--;

            if ((Shifter & 0b10) || (Shifter & 0b1000))
                TR2++;
            else
                if (TR2)
                TR2--;

            if (Shifter & 0b100)
                TR3++;
            else
                if (TR3)
                TR3--;

            SloCtr--;
            if (!SloCtr) {
                SloCtr = 200;
                Shifter <<= 1;
                if (Shifter == 0b10000)
                    Shifter = 1;
            }
        }

        __delay_us(10);
        ctr++;

        if (BTU) {
            LEDR = 0;
            LEDY = 0;
            LEDG = 0;

            UINT8 p;
            for (p = 0; p < sizeof (notes); p++) {
                tone(notes[p], 4000);
            }
            for (p -= 2; p; p--) {
                tone(notes[p], 4000);
            }
            while (BTU) {
            }
        }

        if (BTL) {
            LEDR = 0;
            LEDY = 0;
            LEDG = 0;

            UINT8 p;
            for (p = 0; p < sizeof (MNot); p++) {
                tone(MNot[p], MDur[p] * 80);
            }
            while (BTL) {
            }
        }
    }

}

//t - x100us, T - 1/Hz - x100us

void tone(UINT8 T, UINT16 t) {
    if (T) {
        while (t) {
            BUZZ = 1;
            for (UINT8 i = 0; i < T; i++) {
                __delay_us(40);
            }
            BUZZ = 0;
            for (UINT8 i = 0; i < T; i++) {
                __delay_us(40);
                if (t)
                    t--;
            }
        }
    }
}