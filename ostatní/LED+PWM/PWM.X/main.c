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

void delay(UINT8 cycles);

void main(void) {
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
    
    while(1){
        if(BTL){
            float acc = 0;
            float add = 1;
            for(UINT8 ctr = 0; ctr < 200; ctr++){
                add -= 0.01;
                acc += add;
                RGB_B = 1;
                delay(acc * 5);
                RGB_B = 0;
                delay((50 - acc) * 5);
            }
        }else{
            for(UINT8 duty = 0; duty < 255; duty++){
                RGB_B = 1;
                delay(duty);
                RGB_B = 0;
                delay(255 - duty);
            }
            for(UINT8 duty = 255; duty > 0; duty--){
                RGB_B = 1;
                delay(duty);
                RGB_B = 0;
                delay(255 - duty);
            }
            if(BTU){
                for(UINT8 duty = 0; duty < 255; duty++){
                    RGB_G = 1;
                    delay(duty);
                    RGB_G = 0;
                    delay(255 - duty);
                }
                RGB_G = 1;
                for(UINT8 duty = 0; duty < 255; duty++){
                    RGB_R = 1;
                    delay(duty);
                    RGB_R = 0;
                    delay(255 - duty);
                }
                RGB_R = 1;
                for(UINT8 duty = 255; duty > 0; duty--){
                    RGB_G = 1;
                    delay(duty);
                    RGB_G = 0;
                    delay(255 - duty);
                }
                for(UINT8 duty = 255; duty > 0; duty--){
                    RGB_R = 1;
                    delay(duty);
                    RGB_R = 0;
                    delay(255 - duty);
                }
            }
        }
    }
}

void delay(UINT8 cycles){
    if(cycles){
        for(UINT8 i = 0; i < cycles; i++){
            __delay_us(10);
        }
    }
}