// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)


#include <xc.h>
#include <stdlib.h> 

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

// LED +Cx->Rx- (rezistor je na C -> multiplex po R)

#define C0 RC5   // definice sloupcu
#define C1 RC3
#define C2 RC2
#define C3 RB6
#define C4 RB5

#define R0 RC0  // definice radku
#define R1 RC1
#define R2 RC4
#define R3 RB4
#define R4 RC6
#define R5 RC7
#define R6 RB7

uint8_t tabulka[5] = {
    0b00000000, //?
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

void Multiplex_radek(uint8_t data[5], uint8_t cisloRadku){
    C0 = data[0]>>cisloRadku&1;
    C1 = data[1]>>cisloRadku&1;
    C2 = data[2]>>cisloRadku&1;
    C3 = data[3]>>cisloRadku&1;
    C4 = data[4]>>cisloRadku&1;
}

uint8_t i=0;
void __interrupt() func(){
    if(PIR1bits.T2IF){
        switch(i){
            case 0:
            {
                R6 = 1;
                Multiplex_radek(tabulka, i);
                R0 = 0;
                i++;
                break;
            }
            case 1:
            {
                R0 = 1;
                Multiplex_radek(tabulka, i);
                R1 = 0;
                i++;
                break;
            }
            case 2:
            {
                R1 = 1;
                Multiplex_radek(tabulka, i);
                R2 = 0;
                i++;
                break;
            }
            case 3:
            {
                R2 = 1;
                Multiplex_radek(tabulka, i);
                R3 = 0;
                i++;
                break;
            }
            case 4:
            {
                R3 = 1;
                Multiplex_radek(tabulka, i);
                R4 = 0;
                i++;
                break;
            }
            case 5:
            {
                R4 = 1;
                Multiplex_radek(tabulka, i);
                R5 = 0;
                i++;
                break;
            }
            case 6:
            {
                R5 = 1;
                Multiplex_radek(tabulka, i);
                R6 = 0;
                i=0;
                break;
            }
        }
        PIR1bits.T2IF = 0; // odpoved typu "ano, impulz z citace jsem zpracoval"
    }
    return;            // konec funkce
}

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b11111111;
    TRISB = 0b00001111;
    TRISC = 0b00000000;
    C0=C1=C2=C3=C4=0;
    R0=R1=R2=R3=R4=R5=R6=0;
    srand(rand());
    
    // Konfigurace TMR2 casovace
    INTCONbits.GIE = 1;         // povoli globalni interrupt
    INTCONbits.PEIE = 1;        // povoli interrupt od periferii
    PIE1bits.T2IE = 1;          // povoli interrupt od casovace TMR2
    T2CONbits.T2CKPS = 0b11;    // nastavi TMR2 prescaler (/16)
    T2CONbits.TOUTPS = 0b0001;  // nastavi TMR2 postscaler (/2)
    PR2 = 50;                  // nastavi prahovou hodnoti casovace (T=2ms)
    T2CONbits.TMR2ON = 1;       // zapne funkci casovace
    
    while(1){
        tabulka[4] = tabulka[3];
        tabulka[3] = tabulka[2];
        tabulka[2] = tabulka[1];
        tabulka[1] = tabulka[0];
        tabulka[0] = rand();
        __delay_ms(100);
    }
}