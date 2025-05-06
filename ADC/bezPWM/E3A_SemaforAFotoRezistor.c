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
#define RGBr RA2
#define RGBg RC0
#define RGBb RC1

#define LED8r RC2
#define LED8y RB4
#define LED8g RB5

#define piezo RB6

#define tl1 RA4
#define tl2 RA5

uint8_t chciSvetlo(){
    // vraci 1 kdyz je noc
    uint16_t foto, pot;

    ADCON0 = 0b10100111; //AN9 foto
    ADCON0bits.GO = 1;
    while(ADCON0bits.nDONE);
    foto = 0;
    foto = ADRESH;
    foto = (foto << 8) + ADRESL;

    ADCON0 = 0b10011111; //AN7 pot
    ADCON0bits.GO = 1;
    while(ADCON0bits.nDONE); 
    pot = 0;
    pot = ADRESH;
    pot = (pot << 8) + ADRESL;
    
    if(pot>foto){
        return 1;
    } else {
        return 0;
    }
}

void cekejSPipanim(uint8_t pomalu, uint8_t noc){
    if(tl2){ // kontrola jestli budeme tikat
        for(uint8_t i=0;i<10;i++){
            __delay_ms(100);
        }
    } else {
        if(!noc){
            if(pomalu){
                for(uint8_t i=0; i<10;i++){
                    piezo=1;
                    __delay_ms(100);
                    piezo=0;
                    __delay_ms(100);
                }
            } else {
                piezo=1;
                for(uint8_t i=0;i<5;i++){
                    __delay_ms(100);
                }
                piezo=0;
                for(uint8_t i=0;i<5;i++){
                    __delay_ms(100);
                }
            }
        } else {
            for(uint8_t i=0;i<10;i++){
                __delay_ms(100);
            }
        }
    }
}

void main(void) {
    OSCCON = 0b01110101;
    
    TRISC = 0b11001000;
    TRISA = 0b00111011;
    TRISB = 0b10000000;
    
    ADCON0 = 0b10100111;
    ADCON1 = 0b01010000;

    ANSEL = 0b10000000;
    ANSELH = 0b00000011;

    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    LED8r = 0;
    LED8y = 0;
    LED8g = 0;
    piezo = 0;
    tl1 = 0;
    tl2 = 0;
    
    // semafor
    
    while(!tl1){
        if(chciSvetlo()){
            RGBb=0;
        } else {
            RGBb=1;
        }
    }
    RGBb=0;
    
    while (1){
        if(chciSvetlo()){
            RGBr=0;
            RGBg=0;
            LED8r=0;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(0,1);
            RGBr=0;
            RGBg=0;
            LED8r=0;
            LED8y=1;
            LED8g=0;
            // kontrola jestliprepneme do nocniho rezimu
            cekejSPipanim(0,1);
        } else {
            
            RGBr=0;
            RGBg=1;
            LED8r=1;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(1,0);
            RGBr=1;
            RGBg=0;
            LED8r=1;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(0,0);
            RGBr=1;
            RGBg=0;
            LED8r=1;
            LED8y=1;
            LED8g=0;
            cekejSPipanim(0,0);
            RGBr=1;
            RGBg=0;
            LED8r=0;
            LED8y=0;
            LED8g=1;
            cekejSPipanim(0,0);
            RGBr=1;
            RGBg=0;
            LED8r=0;
            LED8y=1;
            LED8g=0;
            cekejSPipanim(0,0);
            RGBr=1;
            RGBg=0;
            LED8r=1;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(0,0);
        }
    }
}
