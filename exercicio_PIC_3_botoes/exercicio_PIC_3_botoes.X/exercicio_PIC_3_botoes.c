/*
 * File:   exercicio_PIC_3_botoes.c
 * Author: Windows
 *
 * Created on 28 de Fevereiro de 2019, 15:43
 */


#include <xc.h>
#define _XTAL_FREQ 20000000

#pragma CONFIG WTG=OFF

void main(void){
    
    // DEFINE PARA O QUE VAI USAR I/O.
    TRISBbits.TRISB0=1; // BOTÃO.
    TRISBbits.TRISB1=1; // BOTÃO.
    TRISBbits.TRISB2=0; // LED.
    TRISBbits.TRISB3=0; // LED.
    
   while(1){
        if(PORTBbits.RB0==1){
            PORTBbits.RB2=1;
            //__delay_ms(50);
        }
        //else{
            //PORTBbits.RB2=0;
            //__delay_ms(50);
        //}
    }
    
    return;
}
