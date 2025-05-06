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

#define SEG_A RC2
#define SEG_B RC1
#define SEG_C RC0
#define SEG_D RA2
#define SEG_E RC4
#define SEG_F RB4
#define SEG_G RC5
#define tl1 RA4
#define tl2 RA5

#define MAXJAS 127

//      a 
//  f   g   b
//  e       c
//      d

uint8_t PWM = 0;
uint8_t HODMAX = 6;

void nic(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 0;
}

void nula(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 0;
    
}

void jedna(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 0;
}

void dva(){
    SEG_A = 1;
    SEG_B = 0;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 0;
    SEG_F = 1;
    SEG_G = 1;
}

void tri(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 1;
    SEG_G = 1;
}

void ctyri(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 1;
    SEG_F = 0;
    SEG_G = 1;
}

void pet(){
    SEG_A = 0;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 0;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void sest(){
    SEG_A = 0;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void sedm(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 1;
    SEG_G = 0;
}

void osm(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void devet(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 0;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void pismA(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 0;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void pismB(){
    SEG_A = 0;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 0;
    SEG_G = 1;
}

void pismC(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 0;
}

void pismD(){
    SEG_A = 1;
    SEG_B = 1;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 1;
}

void pismE(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 1;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void pismF(){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 0;
    SEG_D = 1;
    SEG_E = 1;
    SEG_F = 1;
    SEG_G = 1;
}

void cislo(uint8_t cislo){
    switch(cislo){
        case 0:
        {
            nula();
            break;
        }
        case 1:
        {
            jedna();
            break;
        }
        case 2:
        {
            dva();
            break;
        }
        case 3:
        {
            tri();
            break;
        }
        case 4:
        {
            ctyri();
            break;
        }
        case 5:
        {
            pet();
            break;
        }
        case 6:
        {
            sest();
            break;
        }
        case 7:
        {
            sedm();
            break;
        }
        case 8:
        {
            osm();
            break;
        }
        case 9:
        {
            devet();
            break;
        }
        case 0xA:
        {
            pismA();
            break;
        }
        case 0xB:
        {
            pismB();
            break;
        }
        case 0xC:
        {
            pismC();
            break;
        }
        case 0xD:
        {
            pismD();
            break;
        }
        case 0xE:
        {
            pismE();
            break;
        }
        case 0xF:
        {
            pismF();
            break;
        }
        default:
        {
            nic();
            break;
        }
        
    }
}

void PWMcisla(uint8_t cislo_in, uint8_t pwm){
    for(uint8_t i=0;i<MAXJAS;i++){
        if(i<pwm){
            cislo(cislo_in);
        } else {
            cislo(17);
        }
    }
}

void animace(uint8_t stav){
    switch (stav){
        case 0:
        {
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        }
        case 1:
        {
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        }
        case 2:
        {
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        }
        case 3:
        {
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 1;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            break;
        }
        case 4:
        {
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 1;
            SEG_F = 0;
            SEG_G = 0;
            break;
        }
        case 5:
        {
            SEG_A = 0;
            SEG_B = 0;
            SEG_C = 0;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 0;
            break;
        }
        default:
        {
            cislo(0);
            break;
        }
    }
    return;
}

uint8_t blik = 0;
uint8_t blikCounter = 0;
uint8_t stavAnimace = 0;
void __interrupt() func(){
    blikCounter++;
    if(blikCounter>=4){
        blik = !blik;
        blikCounter = 0;
        stavAnimace++;
        if(stavAnimace==6){
            stavAnimace=0;
        }
    }
    PIR1bits.T2IF = 0; // odpoved typu "ano, impulz z citace jsem zpracoval"
    return;            // konec funkce
}

/*
    kostka musí házet 1-6
    nastavit, do kolika se má házet
    animace, kdy se hází
    animace zobrazení hozeného ?ísla
    probliknutí ve chvíli, kdy se zobrazí hozené ?íslo
 */

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b00111011; // nastaveni pinu jsko vstupy a vystupy
    TRISB = 0b10000000;
    TRISC = 0b11001000;
    
    ANSELHbits.ANS9 = 1;
    
    ADCON0bits.ADFM = 0;
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 0b1001;
    ADCON0bits.VCFG = 0;
    ADCON1bits.ADCS = 0b010; // correct clock
    
    // Konfigurace TMR2 casovace
    INTCONbits.GIE = 1;         // povoli globalni interrupt
    INTCONbits.PEIE = 1;        // povoli interrupt od periferii
    PIE1bits.T2IE = 1;          // povoli interrupt od casovace TMR2
    T2CONbits.T2CKPS = 0b11;    // nastavi TMR2 prescaler
    T2CONbits.TOUTPS = 0b1111;  // nastavi TMR2 postscaler
    PR2 = 200;                  // nastavi prahovou hodnoti casovace
    T2CONbits.TMR2ON = 1;       // zapne funkci casovace
    
    
    nula();
    uint8_t hod = 1;
    uint8_t nastaveni = 2; // nastaveni=1 tlacitka; nastaveni=2 foto
    uint8_t hazeloSe = 0;
    
    while (1){
        if(nastaveni>=2){
            if(tl2){
                nastaveni=0;
                cislo(HODMAX);
                __delay_ms(250);
            }
            
            if(stavAnimace==5){ // jen pro citani
                // RC7=AN9 (jeden POT)
                ADCON0bits.GO = 1;
                while(ADCON0bits.nDONE){}
                HODMAX = ((ADRESH&0xF0)>>4)+2;
                if(HODMAX>0xF){HODMAX=0xF;}
            }
            
            // funkce pro zachovani blikani
            if(blik){
                cislo(HODMAX);
            } else {
                cislo(17);
            }
        }else if(nastaveni==1){
            if(tl2){
                nastaveni=0;
                cislo(HODMAX);
                __delay_ms(250);
            }
            if(tl1){
                HODMAX++;
                if(HODMAX>0xF){
                    HODMAX = 2;
                }
                for(uint8_t k=0;k<255;k++){
                    cislo(HODMAX);
                    /*
                    if(blik){
                        cislo(HODMAX);
                    } else {
                        cislo(17);
                    }*/
                    __delay_ms(1);
                }
            }
            cislo(HODMAX);
            /*
            if(blik){
                cislo(HODMAX);
            } else {
                cislo(17);
            }
             * */
        } else {
            while(tl1){
                hod++;
                if(hod>HODMAX){
                    hod=1;
                }
                hazeloSe = 1;
                animace(stavAnimace);
            }
            if(hazeloSe){
                for(uint8_t k=0;k<255;k++){
                    PWMcisla(hod,k);
                }
                for(uint8_t k=0;k<3;k++){
                    cislo(17);
                    __delay_ms(50);
                    cislo(hod);
                    __delay_ms(50);
                }
                hazeloSe=0;
            }
            /*if(tl2){
                nastaveni=1;
                cislo(hod);
                __delay_ms(250);
            }*/
            cislo(hod);
        }
    }
}
