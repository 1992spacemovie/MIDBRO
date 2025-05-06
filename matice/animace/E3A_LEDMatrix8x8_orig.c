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

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

#define C0 RA0                  // definice sloupcu
#define C1 RA1
#define C2 RC0
#define C3 RC1
#define C4 RC2
#define C5 RB4
#define C6 RB5
#define C7 RB6

#define R0 RA5
#define R1 RA4
#define R2 RC5
#define R3 RC4
#define R4 RC3
#define R5 RC6
#define R6 RC7
#define R7 RB7

uint8_t stateOfMatrix[] = {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000};

void ScanColumn(uint8_t numberOfColumn){
    C0 = stateOfMatrix[numberOfColumn]>>7&1;
    C1 = stateOfMatrix[numberOfColumn]>>6&1;
    C2 = stateOfMatrix[numberOfColumn]>>5&1;
    C3 = stateOfMatrix[numberOfColumn]>>4&1;
    C4 = stateOfMatrix[numberOfColumn]>>3&1;
    C5 = stateOfMatrix[numberOfColumn]>>2&1;
    C6 = stateOfMatrix[numberOfColumn]>>1&1;
    C7 = stateOfMatrix[numberOfColumn]&1;
}

void ScanMatrix(){
    ScanColumn(0);
    R0=1;
    // __delay_us(10);
    R0=0;
    ScanColumn(1);
    R1=1;
    // __delay_us(10);
    R1=0;
    ScanColumn(2);
    R2=1;
    // __delay_us(10);
    R2=0;
    ScanColumn(3);
    R3=1;
    // __delay_us(10);
    R3=0;
    ScanColumn(4);
    R4=1;
    // __delay_us(10);
    R4=0;
    ScanColumn(5);
    R5=1;
    // __delay_us(10);
    R5=0;
    ScanColumn(6);
    R6=1;
    // __delay_us(10);
    R6=0;
    ScanColumn(7);
    R7=1;
    // __delay_us(10);
    R7=0;
}

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = TRISB = TRISC = 0; // nastaveni pinu jako vystupy; vystup = 0
    C0=C1=C2=C3=C4=C5=C6=C7=0;
    R0=R1=R2=R3=R4=R5=R6=R7=0;
    
    while (1){
        
        ScanMatrix();
    }
}
