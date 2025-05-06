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
#include "charmap.c"

#define _XTAL_FREQ 8000000

typedef unsigned char UINT8;
typedef unsigned short UINT16;

// LED +Cx->Rx-

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

uint8_t movePointer = 0;
uint8_t advancedMode_moveNow = 0;
uint8_t advancedMode_letterPointer = 0;
uint8_t advancedMode_transitionPointer = 0;
uint8_t advancedMode_textLength = 0;

#define rollingSpeed 160 // max 255 min 0 def 160
#define matrixLength 92 // number of lines to roll through
const uint8_t stateOfMatrix[] = {
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b11000001,
                                0b11111111,
                                0b11000001,
                                0b11000001,
                                0b10111110,
                                0b10000000,
                                0b11111100,
                                0b10001000,
                                0b10000100,
                                0b10000100,
                                0b11111000,
                                0b10000000,
                                0b10111000,
                                0b11010100,
                                0b11010100,
                                0b11010100,
                                0b10011000,
                                0b10000000,
                                0b11001000,
                                0b11010100,
                                0b11010100,
                                0b11010000,
                                0b10100000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10111000,
                                0b11000100,
                                0b11000100,
                                0b11000100,
                                0b10111000,
                                0b10000000,
                                0b10000100,
                                0b10111111,
                                0b11000100,
                                0b11000000,
                                0b10100000,
                                0b10000000,
                                0b10111000,
                                0b11010100,
                                0b11010100,
                                0b11010100,
                                0b10011000,
                                0b10000000,
                                0b10011100,
                                0b10100000,
                                0b11000000,
                                0b10100000,
                                0b10011100,
                                0b10000000,
                                0b11111100,
                                0b10001001,
                                0b10000101,
                                0b10000101,
                                0b10001000,
                                0b10000000,
                                0b10111000,
                                0b11010100,
                                0b11010100,
                                0b11010100,
                                0b10011000,
                                0b10000000,
                                0b11111100,
                                0b10001000,
                                0b10000100,
                                0b10000100,
                                0b11111000,
                                0b10000000,
                                0b10111000,
                                0b11000100,
                                0b11000100,
                                0b11000100,
                                0b10111000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b11011111,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000,
                                0b10000000
                                };

uint8_t advancedMode_currentMatrix[5];
uint8_t advancedMode_currentCharacter[5];
uint8_t advancedMode_nextCharacter[5];

uint8_t advancedMode_enable = 1;
void ScanColumn(uint8_t numberOfColumn){
    if(advancedMode_enable){
        C0 = advancedMode_currentMatrix[0]>>numberOfColumn&1;
        C1 = advancedMode_currentMatrix[1]>>numberOfColumn&1;
        C2 = advancedMode_currentMatrix[2]>>numberOfColumn&1;
        C3 = advancedMode_currentMatrix[3]>>numberOfColumn&1;
        C4 = advancedMode_currentMatrix[4]>>numberOfColumn&1;
    } else {
        C0 = stateOfMatrix[movePointer+0]>>numberOfColumn&1;
        C1 = stateOfMatrix[movePointer+1]>>numberOfColumn&1;
        C2 = stateOfMatrix[movePointer+2]>>numberOfColumn&1;
        C3 = stateOfMatrix[movePointer+3]>>numberOfColumn&1;
        C4 = stateOfMatrix[movePointer+4]>>numberOfColumn&1;
    }
}

uint8_t activeRow = 0;
void scanMatrix(){
    switch(activeRow){
        case 0:
        {
            R6=1;
            ScanColumn(0);
            R0=0;           
            activeRow++;
            break;
        }
        case 1:
        {
            R0=1;
            ScanColumn(1);
            R1=0;
            activeRow++;
            break;
        }
        case 2:
        {
            R1=1;
            ScanColumn(2);
            R2=0;
            activeRow++;
            break;
        }
        case 3:
        {
            R2=1;
            ScanColumn(3);
            R3=0;
            activeRow++;
            break;
        }
        case 4:
        {
            R3=1;
            ScanColumn(4);
            R4=0;
            activeRow++;
            break;
        }
        case 5:
        {
            R4=1;
            ScanColumn(5);
            R5=0;
            activeRow++;
            break;
        }
        case 6:
        {
            R5=1;
            ScanColumn(6);
            R6=0;
            activeRow=0;
            break;
        }
    }
}

uint8_t moveTimer = 0;
#define maxPointerValue matrixLength-5
#define maxMoveTimerValue 255-rollingSpeed
void __interrupt() func(){
    if(PIR1bits.T2IF){
        scanMatrix();
        moveTimer++;
        if(moveTimer>=maxMoveTimerValue){
            if(!advancedMode_enable){
                movePointer++;
                if(movePointer>=maxPointerValue){
                    movePointer=0;
                }
            } else {
                advancedMode_moveNow++;
            }
            moveTimer = 0;
        }
        PIR1bits.T2IF = 0; // odpoved typu "ano, impulz z citace jsem zpracoval"
    }
    return;            // konec funkce
}

void currentCharacterLoader(uint8_t character){
    if(character<0x20){
        advancedMode_currentCharacter[0] = 0; 
        advancedMode_currentCharacter[1] = 0; 
        advancedMode_currentCharacter[2] = 0; 
        advancedMode_currentCharacter[3] = 0; 
        advancedMode_currentCharacter[4] = 0; 
    }
    character-=0x20;
    if(character<=51){
        advancedMode_currentCharacter[0] = charMap1[0+5*character]; 
        advancedMode_currentCharacter[1] = charMap1[1+5*character]; 
        advancedMode_currentCharacter[2] = charMap1[2+5*character]; 
        advancedMode_currentCharacter[3] = charMap1[3+5*character]; 
        advancedMode_currentCharacter[4] = charMap1[4+5*character]; 
    } else if(character<=96){
        character -= 51;
        advancedMode_currentCharacter[0] = charMap2[0+5*character]; 
        advancedMode_currentCharacter[1] = charMap2[1+5*character]; 
        advancedMode_currentCharacter[2] = charMap2[2+5*character]; 
        advancedMode_currentCharacter[3] = charMap2[3+5*character]; 
        advancedMode_currentCharacter[4] = charMap2[4+5*character]; 
    } else {
        return;
    }
}

void nextCharacterLoader(uint8_t character){
    if(character<0x20){
        advancedMode_nextCharacter[0] = 0; 
        advancedMode_nextCharacter[1] = 0; 
        advancedMode_nextCharacter[2] = 0; 
        advancedMode_nextCharacter[3] = 0; 
        advancedMode_nextCharacter[4] = 0; 
        return;
    }
    character-=0x20;
    if(character<=51){
        advancedMode_nextCharacter[0] = charMap1[0+5*character]; 
        advancedMode_nextCharacter[1] = charMap1[1+5*character]; 
        advancedMode_nextCharacter[2] = charMap1[2+5*character]; 
        advancedMode_nextCharacter[3] = charMap1[3+5*character]; 
        advancedMode_nextCharacter[4] = charMap1[4+5*character]; 
    } else if(character<=96){
        character -= 51;
        advancedMode_nextCharacter[0] = charMap2[0+5*character]; 
        advancedMode_nextCharacter[1] = charMap2[1+5*character]; 
        advancedMode_nextCharacter[2] = charMap2[2+5*character]; 
        advancedMode_nextCharacter[3] = charMap2[3+5*character]; 
        advancedMode_nextCharacter[4] = charMap2[4+5*character]; 
    } else {
        return;
    }
}

void main(void) {
    ADCON0 = ADCON1 = 0; // zakaze se AD prevodnik
    ANSEL = ANSELH = 0; // nastavi se vsechny piny jako digitalni
    
    OSCCON = 0b01110101; // nastaveni oscilatoru
        
    // Konfigurace TMR2 casovace
    INTCONbits.GIE = 1;         // povoli globalni interrupt
    INTCONbits.PEIE = 1;        // povoli interrupt od periferii
    PIE1bits.T2IE = 1;          // povoli interrupt od casovace TMR2
    T2CONbits.T2CKPS = 0b11;    // nastavi TMR2 prescaler (/16)
    T2CONbits.TOUTPS = 0b0001;  // nastavi TMR2 postscaler (/2)
    PR2 = 50;                  // nastavi prahovou hodnoti casovace (T=2ms)
    T2CONbits.TMR2ON = 1;       // zapne funkci casovace
    
    TRISA = 0b11111111;
    TRISB = 0b00001111;
    TRISC = 0b00000000;
    C0=C1=C2=C3=C4=0;
    R0=R1=R2=R3=R4=R5=R6=0;
    
    char* text = " Toto je pokus o zobrazeni textu na displeji!"; // MAX 51 zn.
    
    advancedMode_textLength = 0; // count rows
    while(text[advancedMode_letterPointer++]!='\0'){
        advancedMode_textLength++;
    }
    
    advancedMode_letterPointer = 0; 
    
    
    while (1){
        if(advancedMode_moveNow){
            switch(advancedMode_transitionPointer){
                case 0:
                {
                    if(advancedMode_letterPointer>=advancedMode_textLength){
                        advancedMode_letterPointer = 0;
                    }
                    currentCharacterLoader(text[advancedMode_letterPointer]);
                    nextCharacterLoader(text[advancedMode_letterPointer+1]);
                    advancedMode_currentMatrix[0] = advancedMode_currentCharacter[0];
                    advancedMode_currentMatrix[1] = advancedMode_currentCharacter[1];
                    advancedMode_currentMatrix[2] = advancedMode_currentCharacter[2];
                    advancedMode_currentMatrix[3] = advancedMode_currentCharacter[3];
                    advancedMode_currentMatrix[4] = advancedMode_currentCharacter[4]; 
                    advancedMode_transitionPointer++;
                    break;
                }
                case 1:
                {
                    advancedMode_currentMatrix[0] = advancedMode_currentCharacter[1];
                    advancedMode_currentMatrix[1] = advancedMode_currentCharacter[2];
                    advancedMode_currentMatrix[2] = advancedMode_currentCharacter[3];
                    advancedMode_currentMatrix[3] = advancedMode_currentCharacter[4];
                    advancedMode_currentMatrix[4] = 0b00000000; 
                    advancedMode_transitionPointer++;
                    break;
                }
                case 2:
                {
                    advancedMode_currentMatrix[0] = advancedMode_currentCharacter[2];
                    advancedMode_currentMatrix[1] = advancedMode_currentCharacter[3];
                    advancedMode_currentMatrix[2] = advancedMode_currentCharacter[4];
                    advancedMode_currentMatrix[3] = 0b00000000;
                    advancedMode_currentMatrix[4] = advancedMode_nextCharacter[0];  
                    advancedMode_transitionPointer++;
                    break;
                }
                case 3:
                {
                    advancedMode_currentMatrix[0] = advancedMode_currentCharacter[3];
                    advancedMode_currentMatrix[1] = advancedMode_currentCharacter[4];
                    advancedMode_currentMatrix[2] = 0b00000000;
                    advancedMode_currentMatrix[3] = advancedMode_nextCharacter[0]; 
                    advancedMode_currentMatrix[4] = advancedMode_nextCharacter[1]; 
                    advancedMode_transitionPointer++;
                    break;
                }
                case 4:
                {
                    advancedMode_currentMatrix[0] = advancedMode_currentCharacter[4];
                    advancedMode_currentMatrix[1] = 0b00000000;
                    advancedMode_currentMatrix[2] = advancedMode_nextCharacter[0]; 
                    advancedMode_currentMatrix[3] = advancedMode_nextCharacter[1];
                    advancedMode_currentMatrix[4] = advancedMode_nextCharacter[2]; 
                    advancedMode_transitionPointer++;
                    break;
                }
                case 5:
                {
                    advancedMode_currentMatrix[0] = 0b00000000; 
                    advancedMode_currentMatrix[1] = advancedMode_nextCharacter[0]; 
                    advancedMode_currentMatrix[2] = advancedMode_nextCharacter[1];
                    advancedMode_currentMatrix[3] = advancedMode_nextCharacter[2];
                    advancedMode_currentMatrix[4] = advancedMode_nextCharacter[3]; 
                    advancedMode_transitionPointer = 0;
                    advancedMode_letterPointer++;
                    break;
                }
            }
            advancedMode_moveNow=0;
        }
    }
}
