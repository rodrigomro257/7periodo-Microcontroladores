/*
 * File:   exercicio_PIC_2_semaforo.c
 * Author: Windows
 *
 * Created on 28 de Fevereiro de 2019, 15:11
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

#pragma CONFIG WTG=OFF

void main(void){
    
    // DEFINE PARA O QUE VAI USAR I/O.
    // DEFINE TODOS OS PINOS PARA OUT. 
    TRISBbits.TRISB0=0;
    TRISBbits.TRISB1=0;
    TRISBbits.TRISB2=0;
    
    while(1){
        // DEFINE ACIONAMENTO. 
        //PORTxbits.Rxy
        PORTBbits.RB0=1; // LIGA VERDE.
        __delay_ms(500); 
        PORTBbits.RB0=0; // DESLIGA VERDE.
        PORTBbits.RB1=1; // AMARELO.
        __delay_ms(1000);
        PORTBbits.RB1=0; // DESLIGA AMARELO.
        PORTBbits.RB2=1; // VERMELHO.
        __delay_ms(3000);
        PORTBbits.RB2=0; // DESLIGA VERMELHO.
    }
    
    
    return;
}
