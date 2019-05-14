#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <plib/usart.h>
#include <p18f4550.h>
#include <xlcd.h>
#include <delays.h>
#include <string.h>
#include <stdbool.h>

#include "relogio_calendario.h"
#include "display.h"
#include "LCD.h"

#define POLY 0x8408 // O QUE ISSO FAZ???
#define _XTAL_FREQ 80000000

#pragma CONFIG WTG=OFF
// NECESSÁRIO PARA USAR O DISPLAY.
#pragma config PBADEN=OFF 

calendario ca;
relogio re;

void main(void){
//INCICIALIZAÇÕES    
    ca.ano = 19;
    ca.mes = 1;
    ca.dia = 1;
    re.hora=0;
    re.minuto=0;
    re.segundo=0;
    
    //TRISDbits.TRISD0=0; // LED.
    T0CONbits.TMR0ON=1; // HABILITA O TIMER 0;
    
    INTCONbits.TMR0IE=1; // HABILITA A FLAG DE INTERRUPÇÃO.
    INTCONbits.TMR0IF=0; // LIMPA A FLAG.
    
    T0CONbits.T08BIT=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.T0CS=0; // UTILIZAR CLOCK INTERNO.
    
    TMR0=2535; // DE ONDE INICIA O CONTADOR. 
    
    T0CONbits.TMR0ON=1;
    
    // INICIALIZAÇÕES DO DISPLAY:
    ADCON1=0;
    
    TRISB=0x00; // SETA TODAS AS B COMO SAÍDA. 
    TRISC=0x00; // SETA TODAS AS C COMO SAÍDA. 

    // AS PORTAS A CONTROLARÃO A EXIBIÇÃO DE UM DISPLAY COM QUAL VARIÁVEL ESTÁ SENDO EXIBIDA. 
    TRISA=0x00000000; // SETA TODAS AS A COMO SAÍDA.
    
    // GAMBIARRA!!!
    TRISAbits.TRISA6=0;
    TRISCbits.TRISC0=0;
    TRISCbits.TRISC1=0;
    TRISCbits.TRISC2=0;
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=0;
    
    TRISDbits.TRISD0=1; // BOTÃO PARA CONTROLAR EXIBIÇÃO.
    TRISDbits.TRISD1=1; // BOTÃO PARA INCREMENTAR MANUALMENTE.
    TRISDbits.TRISD2=0; // CONTROLA ATIVAÇÃO DO DISPLAY DA ESQUERDA PELO TRANSISTOR.
    TRISDbits.TRISD3=0; // CONTROLA ATIVAÇÃO DO DISPLAY DA DIREITA PELO TRANSISTOR.
    
    // HABILITA PRA USAR INTERRUPÇÃO HIGH OU LOW. 
    INTCONbits.GIEH=1; 
    INTCONbits.GIEL=1;
    
    // FORÇA SATURAÇÃO DOS TRANSISTORES. 
    //PORTDbits.RD2=1;
    //PORTDbits.RD3=1;
    
    init_XLCD(); // FUNÇÃO DE INICIALIZAÇÃO DO DISPLAY.
    
    while(1){
        checa_botao_pressionado(&re, &ca);
    }
    return;
}

void __interrupt() pic_isr(void){
    
    // TIMER0 INTERRUPT?
    if(TMR0IF){  
        //PORTBbits.RB0=PORTBbits.RB0+1; // PISCA LED.
        TMR0=2535;
        INTCONbits.TMR0IF=0;
        contador++;
    }
    //if(contador>9){
    if(contador>1){ // PARA FAZER O TEMPO PASSAR MAIS RÁPIDO.
        tratar_relogio(&ca, &re);
        controlador_variavel_display(&re, &ca); // ESTA FUNÇÃO VERIFICA SE ALGUM BOTÃO FOI PRECIONADO E ATUALIZA O VALOR DO DISPLAY.
        //PORTB=display[re.segundo]; // EXIBE O SEGUNDO ATUAL.
        contador=0;
    }
}
