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

void main(void) {
    ADCON0 = ADCON1 = 0;
    ANSEL = ANSELH = 0;
    OSCCON = 0b1110101;
    
    TRISC = 0b11001000;
    TRISB = 0b10000000;
    TRISA = 0b00111011;
    BUZZ = 0;
    RGB_R = 1;
    RGB_G = 0;
    RGB_B = 0;
    LEDR = 1;
    LEDY = 0;
    LEDG = 0;
    
    char delayCount = 0;
    char state = 0;
    char tickCount = 0;
    char onOff = 0;
    char targetTickCount = 10;
    
    while(1){
        switch(state){
            case 0:
                LEDR = 1;       //vse cervená
                RGB_R = 1;
                delayCount = 10;
                break;
                
            case 1:
                LEDY = 1;       //zluta
                delayCount = 10;
                break;
        
            case 2:
                LEDR = 0;       //zelena
                LEDY = 0;
                LEDG = 1;
                delayCount = 30;
                break;
            
            case 3:
                LEDG = 0;       //zluta
                LEDY = 1;
                delayCount = 10;
                break;
        
            case 4:
                LEDY = 0;       //cervena
                LEDR = 1;
                delayCount = 10;
                break;

            case 5:
                RGB_R = 0;      //zelena pro chodce
                RGB_G = 1;
                delayCount = 20;
                targetTickCount = 1;
                break;
        
            case 6:
                RGB_R = 1;      //cervena pro chodce
                RGB_G = 0;
                delayCount = 10;
                targetTickCount = 10;
                break;
        }
        
        for(char i = 0; i < delayCount; i++){   //centralni cekací smycka
            __delay_ms(100);
            tickCount++;
            if(tickCount == targetTickCount){
                tickCount = 0;
                BUZZ = 1;       // tick
                __delay_ms(3);
                BUZZ = 0;
            }
            if(BTU){
                onOff = 1; 
            }
        }
        
        state++;
        if(state > 6){
            state = 0;
            delayCount = 0;
            LEDR = 0;
            RGB_R = 0;
            while(onOff){
                if(delayCount < 10){
                    LEDY = 1;
                }else{
                    LEDY = 0;
                    if(delayCount == 20){
                        delayCount = 0;
                    }
                }
                
                delayCount++;
                __delay_ms(100);
                if(BTU){
                    while(BTU){
                    __delay_ms(1);
                    }
                    onOff = 0;
                    LEDY = 0;
                }
            }
        }
    }
}