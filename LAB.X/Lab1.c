/*
 * First lab for Digital 2 course
 * File:   lab_1.c
 * Author: Juan Castillo
 * Student ID: 17074
 *
 * Created on Jan. 24, 2020
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
// definimos variables para puertos
#define _XTAL_FREQ 4000000//se define frecuencia de trabajo
//variables a utilizar
char Estado = 0;//variable para antirebote de start
char EJ1 = 0;//variable para antirebote de jugador 1
char EJ2 = 1;//variable para antirebote de jugador 2
char i = 3;//variable para decidir el numero del display
char x = 0;//variable que controla al jugador 1
char y = 0;//variable que controla al jugador 2

unsigned char SEGMENTOS[] = {0X3F,0x06,0x5B,0x4F};//display en hexadesimal
unsigned char jugador1[] = {0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//jugador 1 en hexadecimal
unsigned char jugador2[] = {0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//jugador 2 en hexadecimal
void JUEGO ();//funcion juego 

void main(void) {
    OSCCON = 0b110;// se declara el osciloscopio 
    TRISC = 0;//PORTC output
    TRISDbits.TRISD0 = 0;//PORTD7 output led jugador 1 gana
    TRISDbits.TRISD2 = 0;//PORTD2 output led rojo semaforo 
    TRISDbits.TRISD3 = 0;//PORTD3 output led amarillo semaforo
    TRISDbits.TRISD4 = 0;//PORTD4 output led verde semaforo
    TRISDbits.TRISD7 = 0;//PORTD7 output led jugador 2 gana
    TRISDbits.TRISD6 = 0;//PORTD6 output buzzer de inicio
    TRISA = 0; //PORTA output jugador 1
    TRISEbits.TRISE1 = 1; //RE1 input primer jugador
    TRISEbits.TRISE2 = 1; //RE2 input segundo jugador
    TRISEbits.TRISE3 = 1; //RE3 input start del juego
    TRISB = 0; //PORTB output jugador 2
    ANSELH = 0;//entradas y salidas digitales
    ANSEL = 0;//entradas y salidas digitales
   
    while(1){
        //se define el estado unicial de cada salida 
        PORTC = 0;
        PORTA = 0;
        PORTB = 0;
        PORTDbits.RD0 = 0;
        PORTDbits.RD2 = 0;
        PORTDbits.RD3 = 0;
        PORTDbits.RD4 = 0;
        PORTDbits.RD7 = 0;
        PORTDbits.RD6 = 0;
        //se inicia el antirebote del start
        if (PORTEbits.RE3 == 1){
            Estado = 1;
        }
        if (PORTEbits.RE3 == 0 && Estado == 1){ 
            PORTC = SEGMENTOS[i];//se despliega el calor 3 y en el semaforo se enciende led roja
            y=y-1;
            PORTDbits.RD2 = 1;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 0;
            __delay_ms(5);
            i = i-1;
            PORTC = SEGMENTOS[i];//se despliega el calor 2 y en el semaforo se enciende led amarillo
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 1;
            PORTDbits.RD4 = 0;
            __delay_ms(5);
            i = i-1;
            PORTC = SEGMENTOS[i];//se despliega el calor 1 y en el semaforo se enciende led verde
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 1;
            __delay_ms(5);
            i = i-1;
            PORTC = SEGMENTOS[i];//se despliega el calor 0 y en el semaforo se encienden todas las leds
            PORTDbits.RD3 = 1;
            PORTDbits.RD4 = 1;
            Estado = 0;// se limpia la variable del antirebote
            PORTDbits.RD6 = 1;
            __delay_ms(5);
            PORTDbits.RD6 = 0;
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 0;
            y=0;
            x=0;
            JUEGO(); //se llama la funcion juego
        }
    } 
}
    


void JUEGO (){
    while(1){
        if (PORTEbits.RE1 == 1){//programacion para primer jugador
                EJ1 = 1;
            }
        if (PORTEbits.RE1 == 0 && EJ1 == 1){//si se acepta la condicion se desplaza el jugador
            x=x+1;
            PORTA = jugador1[x];
            EJ1 = 0;
        }
        if (x==8){// al llegar a 8 pulzaciones se detiene al otro jugador y se enciende led de ganador
            __delay_ms(2);
            PORTB =0;
            PORTA = 0;
            PORTDbits.RD0 = 1;
            PORTC = SEGMENTOS[1];
            EJ2=0;
            y=0;
        }
        if(x==9){//apaga todo y se recetea el juego 
            EJ2=0;
            PORTB=0;
            PORTA=0;
            PORTC = 0;
            y=0;
            x=0;
            i=3;
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 0;
            PORTDbits.RD0 = 0;
            return; 
        }    
        if (PORTEbits.RE2 == 1){//programacion para segundo jugador
            EJ2 = 1;
            
        }
        if (PORTEbits.RE2 == 0 && EJ2 == 1){//si se acepta la condicion se desplaza el jugador
            y=y+1;
            PORTB = jugador2[y];
            EJ2 = 0;
        }
        if (y==9){// al llegar a 9 pulzaciones se detiene al otro jugador y se enciende led de ganador
            __delay_ms(2);
            PORTB = 0;
            PORTDbits.RD7 = 1;
            PORTC = SEGMENTOS[2];
            EJ1=0;
            x=0;
            PORTA = 0;
        }
        if(y==10){//apaga todo y se recetea el juego 
            PORTA = 0;
            PORTB = 0;
            PORTC = 0;
            EJ1=0;
            x=0;
            y=0;
            i=3;
            PORTDbits.RD2 = 0;
            PORTDbits.RD3 = 0;
            PORTDbits.RD4 = 0;
            PORTDbits.RD7 = 0;
            return; 
    }    
}
}