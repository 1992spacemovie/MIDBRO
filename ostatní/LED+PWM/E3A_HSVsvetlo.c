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
#define tl2Akt RA5

/*
naprogramovat pripravek tak, ?e:
1. bude mit 4 módy (nastaveni a HSV)
2. v prvnim nastavovacim modu sviti cervena ledka (nastavuje se odstin barvy)
3. v druhym nastavovacim modu sviti oranzova ledka (nastavuje se saturace - prolinani barva/bila)
4. v tretim nastavovacim modu sviti zelena ledka (nastavuje se value - jas barvy - od nizke po vysoke)
*/

void PWM(uint8_t r, uint8_t g, uint8_t b){
    uint8_t k = 0;
    //RGBr = RGBb = RGBg = 1;
    while(k<255){
        if(k<r){
            RGBr=1;
        }
        if(k<g){
            RGBg=1;
        }
        if(k<b){
            RGBb=1;
        }
        if(k==r){
            RGBr=0;
        }
        if(k==g){
            RGBg=0;
        }
        if(k==b){
            RGBb=0;
        }
        k++;
    }
    return;
}

void beep(){
    for(uint8_t a=0;a<50;a++){
        piezo=1;
        __delay_us(500);
        piezo=0;
        __delay_us(500);
    }
}

uint8_t tl2Mem = 0;

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
    uint8_t tl2 = 0;
    
    uint8_t mod = 0;
    
    uint8_t barvaR = 255;
    uint8_t barvaG = 0;
    uint8_t barvaB = 0;
    uint8_t modBarvy = 0;
    
    uint8_t saturace = 0;
    uint8_t jas = 254;
    
    
    uint8_t celkemR = 255;
    uint8_t celkemG = 0;
    uint8_t celkemB = 0;
    
    while (1){
        //R_TRIG pro tl.2
        if(tl2Akt != tl2Mem){
            tl2=tl2Akt;
        }
        tl2Mem = tl2Akt;
        // smycka
        switch (mod){
            case 0: // pracovni rezim
            {
                // tlacitka
                if(tl2){
                    // dalsi mod
                    mod++;
                    LED8r = 1;
                    beep();
                }
                break;
            }
            case 1:
            {
                // rezim nastaveni barvy
                i-++++*-+*---+
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                +*
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                +***********f(tl1){
                    if(modBarvy==0){
                        barvaB++;
                        if(barvaB==255){
                            modBarvy++;
                        }
                    }
                    else if(modBarvy==1){
                        barvaR--;
                        if(barvaR==0){
                            modBarvy++;
                        }
                    }
                    else if(modBarvy==2){
                        barvaG++;
                        if(barvaG==255){
                            modBarvy++;
                        }
                    }
                    else if(modBarvy==3){
                        barvaB--;
                        if(barvaB==0){
                            modBarvy++;
                        }
                    }
                    else if(modBarvy==4){
                        barvaR++;
                        if(barvaR==255){
                            modBarvy++;
                        }
                    }
                    else if(modBarvy==5){
                        barvaG--;
                        if(barvaG==0){
                            modBarvy=0;
                        }
                    }
                }
                if(tl2){
                    // dalsi mod
                    mod++;
                    LED8r=0;
                    LED8y=1;
                    beep();
                }
                break;
            }
            case 2:
            {
                // rezim nastaveni saturace barvy
                if(tl1){
                    // cyklovani mezi saturacemi
                    if(saturace==254){
                        saturace=0;
                    }
                    saturace++;
                }
                if(tl2){
                    // dalsi mod
                    LED8y=0;
                    LED8g=1;
                    beep();
                    mod++;
                }
                break;
            }
            case 3:
            {
                // rezim nastaveni jasu
                if(tl1){
                    // cyklovani mezi jasem
                    if(jas==254){
                        jas=0;
                    }
                    jas++;
                }
                if(tl2){
                    // dalsi mod
                    mod=0;
                    LED8g=0;
                    beep();
                }
                break;
            }
        }
        if(mod!=0){
            uint16_t korekceR = ((saturace*(255-barvaR))/255);
            uint16_t korekceG = ((saturace*(255-barvaG))/255);
            uint16_t korekceB = ((saturace*(255-barvaB))/255);
            uint8_t satR = barvaR + korekceR;
            uint8_t satG = barvaG + korekceG;
            uint8_t satB = barvaB + korekceB;
            celkemR = (satR*jas)/255;
            celkemG = (satG*jas)/255;
            celkemB = (satB*jas)/255;
        }
        PWM(celkemR,celkemG,celkemB);
        // reset R_TRIG
        tl2=0;
    }
}
