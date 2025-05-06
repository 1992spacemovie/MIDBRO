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
// RC0 RC1 RA2
#define A4 RA1
#define A3 RA2
#define A2 RC0
#define A1 RC1
#define B4 RC2
#define B3 RB4
#define B2 RB5
#define B1 RB6

#define piezo RC7

typedef union {
    struct {
         unsigned T1 :1;
         unsigned T2 :1;
         unsigned T3 :1;
         unsigned T4 :1;
         unsigned T5 :1;
         unsigned T6 :1;
         unsigned T7 :1;
         unsigned T8 :1;
         unsigned T9 :1;
         unsigned T0 :1;
         unsigned TH :1;
         unsigned TK :1;
         unsigned TA :1;
         unsigned TB :1;
         unsigned TC :1;
         unsigned TD :1;
    };
} matrixState_t;

matrixState_t matrixState;

void updateMatrixState(){
    A1=1;
    matrixState.T1 = B1;
    matrixState.T4 = B2;
    matrixState.T7 = B3;
    matrixState.TH = B4;
    A1=0;
    A2=1;
    matrixState.T2 = B1;
    matrixState.T5 = B2;
    matrixState.T8 = B3;
    matrixState.T0 = B4;
    A2=0;
    A3=1;
    matrixState.T3 = B1;
    matrixState.T6 = B2;
    matrixState.T9 = B3;
    matrixState.TK = B4;
    A3=0;
    A4=1;
    matrixState.TA = B1;
    matrixState.TB = B2;
    matrixState.TC = B3;
    matrixState.TD = B4;
    A4=0;
    return;
}

void main(void) {
    OSCCON = 0b01110101;
    
    TRISC = 0b01001100;
    TRISA = 0b00111001;
    TRISB = 0b01110000;
    
    ADCON0 = 0b10100111;
    ADCON1 = 0b01010000;

    ANSEL = 0b10000000;
    ANSELH = 0b00000011;
    
    piezo = 0;
        
    while (1){
        updateMatrixState();
        uint8_t buzzer = 0;
        // tady probehne if na tony
        
        if(matrixState.TD){buzzer = 1;}
        else if(matrixState.TK){buzzer = 16;}
        else if(matrixState.T0){buzzer = 32;}
        else if(matrixState.TH){buzzer = 48;}
        else if(matrixState.TC){buzzer = 64;}
        else if(matrixState.T9){buzzer = 80;}
        else if(matrixState.T8){buzzer = 96;}
        else if(matrixState.T7){buzzer = 112;}
        else if(matrixState.TB){buzzer = 128;}
        else if(matrixState.T6){buzzer = 144;}
        else if(matrixState.T5){buzzer = 160;}
        else if(matrixState.T4){buzzer = 176;}
        else if(matrixState.TA){buzzer = 192;}
        else if(matrixState.T3){buzzer = 208;}
        else if(matrixState.T2){buzzer = 224;}
        else if(matrixState.T1){buzzer = 240;}
        else{ buzzer=0;}
                
        // buzzer zde
        if(buzzer>0){
            piezo=1;
            for(uint8_t i=0;i<buzzer;i++){
                __delay_us(5);
            }
            piezo=0;
            for(uint8_t i=0;i<buzzer;i++){
                __delay_us(5);
            }
        }
    }
}
