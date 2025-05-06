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
#include <stdio.h>
#include <stdlib.h> 

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

#define TL1 RA5
#define POT1 RC3
#define PIEZO RB6
#define LED8r RC2

#define LCD_D7 RA4
#define LCD_D6 RA0
#define LCD_D5 RC5
#define LCD_D4 RA1
#define LCD_D3 RC4
#define LCD_D2 RA2
#define LCD_D1 RC6
#define LCD_D0 RC0

#define LCD_EN RC7
#define LCD_RW RC1 // RW = 0-Write, 1-Read
#define LCD_RS RB4 // log.1 - DATA, log.0 - instrukce

#define LCD_INSTR_CLR 0b00000001
#define LCD_INSTR_RETURN_HOME 0b00000010

uint32_t pot;
uint8_t mode=0;

uint16_t reakceTimer = 0;
uint8_t reakceBezi = 0;

void lcd_instruction(uint8_t data, uint8_t instr){
    LCD_RS = data&1;
    LCD_RW = 0;
    asm("nop");
    asm("nop");
    LCD_EN = 1;
    LCD_D0 = instr&1;
    LCD_D1 = instr>>1&1;
    LCD_D2 = instr>>2&1;
    LCD_D3 = instr>>3&1;
    LCD_D4 = instr>>4&1;
    LCD_D5 = instr>>5&1;
    LCD_D6 = instr>>6&1;
    LCD_D7 = instr>>7&1;
    asm("nop");
    asm("nop");
    LCD_EN = 0;
    __delay_ms(1);
}

void lcd_init(){
    __delay_ms(15);
    lcd_instruction(0,0b00110000); // Function set - RST
    __delay_ms(10); // 4.1ms delay
    lcd_instruction(0,0b00110000); // Function set - RST 
    __delay_ms(1); // 100us delay
    lcd_instruction(0,0b00110000); // Function set - RST 100us delay
    __delay_ms(1); // 100us delay
    
    lcd_instruction(0,0b00111000); // Function set - 2lin, 5x8 
    __delay_ms(1); // 100us delay
    lcd_instruction(0,0b00001000); // Display off 
    __delay_ms(2); // 2ms delay
    lcd_instruction(0,0b00000001); // Clear display
    __delay_ms(10); // 100us delay
    lcd_instruction(0,0b00000110); // entry mode set - increment, no shift
    __delay_ms(10);
    lcd_instruction(0,0b00001100); // Display on, Cur off, blink - TEST
    __delay_ms(2); // 2ms delay
}

void lcd_write_to_place(uint8_t row, char *text){
    // 0x40 secondline
    if(row==0){
        lcd_instruction(0, 0b10000000);
    } else {
        lcd_instruction(0, 0b11000000);
    }
    while(*text){
        lcd_instruction(1,*text);
        text++;
    }
}

uint8_t vlakHodiny[9];
const uint8_t *vlakOdjezd = "       Ceska Lipa hl.n.";
#define vlakOdjezdDelka 23
uint8_t vlakOdjezdZobraz[9];
uint8_t vlakOdjezdPozice = 0;
uint8_t blik = 0;
void blikaniHodin(){
    if(blik==0){
        sprintf((char*)&vlakHodiny, "15:23   ");
        blik=1;
    } else {
        sprintf((char*)&vlakHodiny, "        ");
        blik=0;
    }
}

void moveTextNadrazi(){
    for(uint8_t i=0;i<8;i++){
        if(vlakOdjezdPozice+i>=vlakOdjezdDelka){
            vlakOdjezdZobraz[i] = ' ';
        } else {
            vlakOdjezdZobraz[i] = vlakOdjezd[vlakOdjezdPozice+i];
        }
    }
    
    if(vlakOdjezdPozice>=vlakOdjezdDelka){
        vlakOdjezdPozice=0;
    } else {
        vlakOdjezdPozice++;
    }
}

uint8_t uartMem[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint8_t uartPos = 0;
void uartDisplay(){
    lcd_instruction(0, 0b10000000);
    uint8_t b=0;
    while(b<8){
        if(uartMem[b]==0){lcd_instruction(1,' ');} else {
            lcd_instruction(1,uartMem[b]);
        }
        b++;
    }
    lcd_instruction(0, 0b11000000);
    while(b<16){
        if(uartMem[b]==0){lcd_instruction(1,' ');} else {
            lcd_instruction(1,uartMem[b]);
        }
        b++;
    }
}

uint8_t textMovingTimer = 0;
uint8_t halfSecond = 3;
uint8_t oneSecond = 0;
uint8_t podpisPosun = 0;
uint16_t stopky = 0;
uint8_t stopkyS = 0;
void __interrupt() func(){
    if(PIR1bits.T2IF){
        textMovingTimer++;
        if(textMovingTimer>=100){
            if(mode==1){
                moveTextNadrazi();
            }
            textMovingTimer=0;
        }
        
        halfSecond++;
        if(halfSecond>=150){
            blikaniHodin();
            halfSecond=0;
        }
        
        oneSecond++;
        if(oneSecond>250){
            oneSecond=0;
            podpisPosun++;
            if(podpisPosun>=8){
                podpisPosun=0;
            }
        }
        
        if(mode==3){
            PIEZO = !PIEZO;
            if(halfSecond==0){
                LED8r = !LED8r;
            }
        }
        
        stopky+=3;
        if(stopky>=1000){
            stopkyS++;
            stopky=0;
            if(stopkyS==100){
                stopkyS=0;
            }
        }
        
        if(reakceBezi && reakceTimer<65000){
            reakceTimer+=3;
        }
        
        PIR1bits.T2IF = 0; // odpoved typu "ano, impulz z citace jsem zpracoval"
    }
    if(PIR1bits.RCIF){
        if(RCSTAbits.OERR){
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
        
        if(RCSTAbits.FERR){
            RCREG;
        }
        
        if(uartPos<16){
            uartMem[uartPos++] = RCREG;
        } else {
            for(uint8_t k=0;k<15;k++){
                uartMem[k] = uartMem[k+1];
            }
            uartMem[15] = RCREG;
        }
        
        PIR1bits.RCIF = 0;
    }
    return;            // konec funkce
}

const uint8_t podpis1[9] = "        ";
const uint8_t podpis2[9] = "E4A 2024";
const uint8_t podpis3[9] = "  PSLIB ";
const uint8_t podpis4[9] = "pslib.cz";
const uint8_t podpis5[9] = "CC-BY-SA";
const uint8_t podpis6[9] = "        ";
const uint8_t podpis7[9] = "Its done";
const uint8_t podpis8[9] = "The end!";

void zobrazPodpis(){
    lcd_instruction(0, 0b10000000);
    for(uint8_t v=0;v<8;v++){
        if(podpisPosun==0){
            lcd_instruction(1,podpis1[v]);
        } else if(podpisPosun==1){
            lcd_instruction(1,podpis2[v]);
        } else if(podpisPosun==2){
            lcd_instruction(1,podpis3[v]);
        } else if(podpisPosun==3){
            lcd_instruction(1,podpis4[v]);
        } else if(podpisPosun==4){
            lcd_instruction(1,podpis5[v]);
        } else if(podpisPosun==5){
            lcd_instruction(1,podpis6[v]);
        } else if(podpisPosun==6){
            lcd_instruction(1,podpis7[v]);
        } else if(podpisPosun==7){
            lcd_instruction(1,podpis8[v]);
        }
    }
    lcd_instruction(0, 0b11000000);
    for(uint8_t v=0;v<8;v++){
        if(podpisPosun==0){
            lcd_instruction(1,podpis2[v]);
        } else if(podpisPosun==1){
            lcd_instruction(1,podpis3[v]);
        } else if(podpisPosun==2){
            lcd_instruction(1,podpis4[v]);
        } else if(podpisPosun==3){
            lcd_instruction(1,podpis5[v]);
        } else if(podpisPosun==4){
            lcd_instruction(1,podpis6[v]);
        } else if(podpisPosun==5){
            lcd_instruction(1,podpis7[v]);
        } else if(podpisPosun==6){
            lcd_instruction(1,podpis8[v]);
        } else if(podpisPosun==7){
            lcd_instruction(1,podpis1[v]);
        }
    }
}

uint8_t tlBprev=0;
uint8_t tlB_R_TRIG=0;
const uint8_t napeti1[9] = "Napeti: ";
uint8_t napeti2[9];
const uint8_t errorRow1[9] = "Error   ";
const uint8_t errorRow2[9] = "     404";
const uint8_t reakceRow1[9] = "Reakce: ";
uint8_t reakceRow2[9] = "---- ms ";
uint8_t gameRow1[9] = "Nasobky ";
uint8_t gameRow2[9] = "c.      ";
const uint8_t stopkyRow1[9] = "'Stopky'";
uint8_t stopkyRow2[9] = "00.000 s";
void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    ANSELbits.ANS7 = 1;
    ADCON0 = 0b10100111;
    ADCON1 = 0b01010000;
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
    
    TRISA = 0b00100000;
    TRISB = 0b00000000;
    TRISC = 0b00001000;
    
    // Konfigurace TMR2 casovace
    INTCONbits.GIE = 1;         // povoli globalni interrupt
    INTCONbits.PEIE = 1;        // povoli interrupt od periferii
    PIE1bits.T2IE = 1;          // povoli interrupt od casovace TMR2
    T2CONbits.T2CKPS = 0b11;    // nastavi TMR2 prescaler (/16)
    T2CONbits.TOUTPS = 0b1111;  // nastavi TMR2 postscaler (/16)
    PR2 = 25;                  // nastavi prahovou hodnoti casovace (T=2ms)
    T2CONbits.TMR2ON = 1;
    
    // UART RX setup
    RCSTAbits.CREN = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    PIE1bits.RCIE = 1;
    
    
    LCD_D7 = LCD_D6 = LCD_D5 = LCD_D4 = LCD_D3 = LCD_D2 = LCD_D1 = LCD_D0 = 0;
    LCD_EN = 0;
    LCD_RW = 0;
    LCD_RS = 0;
        
    lcd_init();
    
    while(1){
        if(TL1!=tlBprev){
            tlBprev = TL1;
            if(TL1){
                tlB_R_TRIG=1;
            }
        } else {
            tlB_R_TRIG=0;
        }
        
        switch(mode){
            case 0: // Voltmetr
            {
                // dostat data z potA
                ADCON0 = 0b10011111; //AN7 pot
                ADCON0bits.GO = 1;
                while(ADCON0bits.nDONE);
                pot = (ADRESH<<8) + ADRESL;
                pot = pot * 5000;
                pot = pot / 1024;

                lcd_write_to_place(0,(char*)&napeti1);
                sprintf((char*)&napeti2, "%04d mV ",pot);
                lcd_write_to_place(1,(char*)&napeti2);
                
                if(tlB_R_TRIG){
                    mode++;
                }
                break;
            }
            case 1: // vlak
            {
                lcd_write_to_place(0,(char*)&vlakHodiny);
                lcd_write_to_place(1,(char*)&vlakOdjezdZobraz);
                      
                if(tlB_R_TRIG){
                    mode++;
                }
                break;
            }
            case 2: // UART
            {
                uartDisplay();
                if(tlB_R_TRIG){
                    mode++;
                }
                break;
            }
            case 3: // Bzucak
            {
                lcd_write_to_place(0,(char*)&errorRow1);
                lcd_write_to_place(1,(char*)&errorRow2);
                
                if(tlB_R_TRIG){
                    PIEZO = 0;
                    mode++;
                }
                break;
            }
            case 4: // Reakce
            {
                LED8r = 0;
                lcd_write_to_place(0,(char*)&reakceRow1);
                sprintf((char*)&reakceRow2, "----- ms",reakceTimer);
                lcd_write_to_place(1,(char*)&reakceRow2);
                __delay_ms(5000);
                uint8_t cekej = rand();
                for(uint8_t k=0;k<cekej;k++){
                    __delay_ms(5);
                }
                while(TL1){}
                LED8r = 1;
                reakceBezi = 1;
                while(!TL1){PIEZO=!PIEZO;}
                reakceBezi = 0;
                LED8r = 0;
                sprintf((char*)&reakceRow2, "%05d ms",reakceTimer);
                lcd_write_to_place(1,(char*)&reakceRow2);
                while(TL1){}
                __delay_ms(250);
                reakceTimer = 0;
                for(uint8_t p=0;p<150;p++){
                    if(TL1){
                        mode++;
                        while(TL1){}
                        break;
                    }
                    __delay_ms(25);
                }
                break;
            }
            case 5: // Numbers Game
            {
                /*
                 * Popis hry:
                 * Pocitaji se cisla, na nasobky x se provede vyhodnoceni
                 * kdyz se uzivatel trefi, skore se pricte
                 * kdyz ne, system ho vybzuci
                 */
                
                uint8_t nasobek = (rand()%5)+3;
                sprintf((char*)&gameRow1, "Nasobky ");
                lcd_write_to_place(0,(char*)&gameRow1);
                
                uint8_t odchod = 0;
                
                for(uint8_t n=3;n>0;n--){
                    sprintf((char*)&gameRow2, "c. %d  -%d",nasobek, n);
                    lcd_write_to_place(1,(char*)&gameRow2);
                    for(uint8_t v=0;v<100;v++){
                        __delay_ms(10);
                        if(TL1){
                            while(TL1){}
                            odchod = 1;
                            n=1;
                            v=101;
                        }
                    }
                }
                if(odchod){
                    mode++;
                    break;
                }
                
                uint8_t skore = 0;
                uint8_t spatne = 0;
                for(uint16_t g=1;g<65000;g++){
                    LED8r=0;
                    
                    uint8_t prekvapeni = rand();
                    if(prekvapeni&1){
                        g++;
                    }

                    sprintf((char*)&gameRow1, "=> %05d",g);
                    lcd_write_to_place(0,(char*)&gameRow1);
                    sprintf((char*)&gameRow2, "%03d bodu",skore);
                    lcd_write_to_place(1,(char*)&gameRow2);

                    uint8_t z=0;
                    if(g<10){
                        z=100;
                    } else if(g<33) {
                        z=75;
                    } else if(g<60) {
                        z=50;
                    } else {
                        z=30;
                    }
                    uint8_t ok = g%nasobek;
                    while(z>0){

                        if(TL1){
                            if(ok==0){
                                skore++;
                                sprintf((char*)&gameRow2, "%03d bodu",skore);
                                lcd_write_to_place(1,(char*)&gameRow2);
                                ok = 1;
                            } else {
                                spatne = 1;
                                g=65001;
                            }
                            z=1;
                        }
                        if(z==1 && ok==0){
                            spatne = 1;
                            g=65001;
                        }
                        while(TL1){}
                        __delay_ms(10);
                        z--;
                        
                    }
                }
                if(spatne){
                    LED8r = 1;
                    while(TL1){}
                    sprintf((char*)&gameRow1, "Spatne! ");
                    lcd_write_to_place(0,(char*)&gameRow1);
                    while(!TL1){PIEZO=!PIEZO;}
                    while(TL1){}
                    spatne=0;
                    LED8r=0;
                }
                break;
            }
            case 6: // "stopky"
            {
                
                lcd_write_to_place(0,(char*)&stopkyRow1);
                sprintf((char*)&stopkyRow2, "%02d.%03d s", stopkyS, stopky);
                lcd_write_to_place(1,(char*)&stopkyRow2);
                if(tlB_R_TRIG){
                    podpisPosun=0;
                    PIEZO = 0;
                    mode++;
                }
                break;
            }
            case 7: // podpis/titulky
            {
                zobrazPodpis();
                if(tlB_R_TRIG){
                    PIEZO = 0;
                    mode=0;
                }
                break;
            }
        }
    }
}