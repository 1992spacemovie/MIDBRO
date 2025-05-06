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

uint8_t muzeSePrepnout = 1;

void kontrolaPusteniTlacitka(){
    if(!tl1){
        muzeSePrepnout=1;
    }
}

void cekejSPipanim(uint8_t pomalu, uint8_t noc){
    kontrolaPusteniTlacitka();
    if(tl2){ // kontrola jestli budeme tikat
        for(uint8_t i=0;i<10;i++){
            __delay_ms(100);
            kontrolaPusteniTlacitka();
        }
    } else {
        if(!noc){
            if(pomalu){
                for(uint8_t i=0; i<10;i++){
                    piezo=1;
                    __delay_ms(100);
                    kontrolaPusteniTlacitka();
                    piezo=0;
                    __delay_ms(100);
                    kontrolaPusteniTlacitka();
                }
            } else {
                piezo=1;
                for(uint8_t i=0;i<5;i++){
                    __delay_ms(100);
                    kontrolaPusteniTlacitka();
                }
                piezo=0;
                for(uint8_t i=0;i<5;i++){
                    __delay_ms(100);
                    kontrolaPusteniTlacitka();
                }
            }
        } else {
            for(uint8_t i=0;i<10;i++){
                __delay_ms(100);
                kontrolaPusteniTlacitka();
            }
        }
    }
    kontrolaPusteniTlacitka();
}

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b00111011; // nastaveni pinu jsko vstupy a vystupy
    TRISB = 0b10000000;
    TRISC = 0b11001000;

    RGBr = 0;
    RGBg = 0;
    RGBb = 0;
    LED8r = 0;
    LED8y = 0;
    LED8g = 0;
    piezo = 0;
    tl1 = 0;
    tl2 = 0;
    
    // vyrobit semafor -> L0 (jenom blikání LED)
                        //L1 (jedno tlacítko nocní rezim)
                        //L2 (plus pri stisknutem tlacitku zvuk pro slepce)
    
    uint8_t noc = 0;
    
    while (1){
        if(noc){
            RGBr=0;
            RGBg=0;
            LED8r=0;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(0,noc);
            RGBr=0;
            RGBg=0;
            LED8r=0;
            LED8y=1;
            LED8g=0;
            // kontrola jestli prepneme do nocniho rezimu
            cekejSPipanim(0,noc);
            if(tl1 && muzeSePrepnout){
                noc=0;
                muzeSePrepnout=0;
            }
        } else {
            
            RGBr=0;
            RGBg=1;
            LED8r=1;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(1,noc);
            RGBr=1;
            RGBg=0;
            LED8r=1;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(0,noc);
            RGBr=1;
            RGBg=0;
            LED8r=1;
            LED8y=1;
            LED8g=0;
            cekejSPipanim(0,noc);
            RGBr=1;
            RGBg=0;
            LED8r=0;
            LED8y=0;
            LED8g=1;
            cekejSPipanim(0,noc);
            RGBr=1;
            RGBg=0;
            LED8r=0;
            LED8y=1;
            LED8g=0;
            cekejSPipanim(0,noc);
            RGBr=1;
            RGBg=0;
            LED8r=1;
            LED8y=0;
            LED8g=0;
            cekejSPipanim(0,noc);
            
            // NOC KONTROLA
            if(tl1 && muzeSePrepnout){
                noc=1;
                muzeSePrepnout=0;
            }
        }
    }
}
