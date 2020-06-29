/* 
 * File:   serial.h
 * Author: Windows
 *
 * Created on 29 de Maio de 2019, 09:14
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include "display_LCD.h"
#include "relogio.h"

unsigned char rx_data(void);
unsigned char serial_data;

unsigned char BUFF_COM[7];
unsigned char BUFF_RESP[7];

#define FREQ 20000000 // DEFINE FREQUENCIA.
#define _XTAL_FREQ 20000000
#define baud 9600
#define spbrg_value (((FREQ/64)/baud)-1) // Refer to the formula for Baud rate calculation in Description tab
/*
#define ESPERA_COMANDO 0x00
#define COMANDO_RECEBIDO 0x01
#define VERIFICAR_COMANDO 0x02
#define COMANDO_OK 0x03
#define COMANDO_NOK 0x04
#define ENVIA_RESPOSTA 0x05

#define COMANDO_LEITURA 0x01
#define COMANDO_ALTERACAO 0x02

#define HORA 0x01
#define DATA 0x02
#define DESPERTADOR 0x03
*/
#define ESPERA_COMANDO '0'
#define COMANDO_RECEBIDO '1'
#define VERIFICAR_COMANDO '2'
#define COMANDO_OK '3'
#define COMANDO_NOK '4'
#define ENVIA_RESPOSTA '5'

#define COMANDO_LEITURA '1'
#define COMANDO_ALTERACAO '2'

#define HORA '1'
#define DATA '2'
#define DESPERTADOR '3'
 
int ESTADO_COMUNICACAO;

void tx_data() {
    int cont;
    while (!TXIF);

    for (cont=0; cont<7; cont++) {
        while (!TXIF);
        TXREG = BUFF_RESP[cont];
    }
    ESTADO_COMUNICACAO = ESPERA_COMANDO;
}

unsigned char rx_data(void){
    while(!RCIF); // Wait until RCIF gets low
    return RCREG; // Retrieve data from reception register
} 

void verifica_comando(){
    // NÃO PREOCUPAR COM ISSO POR ENQUANTO. 
    ESTADO_COMUNICACAO = COMANDO_OK;
}

void gambiarra_pro_serial(){
    // GAMBIARRA DE TESTE.
    // EXIBE NO DISPLAY O QUE FOI LIDO DO TERMINAL.
    WriteCmdXLCD(0x0C); // DESLIGA O CURSOR. 
    SetDDRamAddr(0x00);
    sprintf(str, "%d %d %d %d %d %d %d", BUFF_COM[0]-48, BUFF_COM[1]-48, BUFF_COM[2]-48, BUFF_COM[3]-48, BUFF_COM[4]-48, BUFF_COM[5]-48, BUFF_COM[6]-48);
    putrsXLCD(str);
    SetDDRamAddr(0x40); // POSICIONA O CURSOR NA LINHA 2. 
    sprintf(str, "%d %d %d %d %d %d %d", BUFF_RESP[0]-48, BUFF_RESP[1]-48, BUFF_RESP[2]-48, BUFF_RESP[3]-48, BUFF_RESP[4]-48, BUFF_RESP[5]-48, BUFF_RESP[6]-48);
    putrsXLCD(str);    
}

void trata_comando(){
    // LED FICA PISCANDO AQUI.
    PORTCbits.RC0=1; // TESTE.
    __delay_ms(180);
    PORTCbits.RC0=0; // TESTE.
    
    //gambiarra_pro_serial();
    
    /*
    // ISSO PROVA QUE OS VALORES DO BUFFER SÃO SEMPRE ZERO.
    if(BUFF_COM[0]==0){
        PORTCbits.RC0=1; // TESTE.
        __delay_ms(180);
        PORTCbits.RC0=0; // TESTE.
    }
     */ 
    
    // ANALIZA O PRIMEIRO COMANDO DO TERMINAL.   
	switch(BUFF_COM[0]){ // 1==LEITURA. 2==ESCRITA.
        
        // SE O PRIMEIRO COMANDO FOR 1. 
		case COMANDO_LEITURA: 
            
            BUFF_RESP[0] = BUFF_COM[0];
            BUFF_RESP[1] = BUFF_COM[1];

            // ANALIZA O SEGUNDO COMANDO DO TERMINAL.
			switch(BUFF_COM[1]){ // 1==HORA. 2==DATA. 3==DESPERTADOR.
                
                // SE O SEGUNDO COMANDO FOR 1.
				case HORA:
                    BUFF_RESP[2]=Relogio.hora;
                    //BUFF_RESP[3]=Relogio.minuto%10;
                    //BUFF_RESP[4]=Relogio.segundo%10;
					BUFF_RESP[5]=0xFF;
					BUFF_RESP[6]=0xFF;
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                    break;
                    
                // SE O SEGUNDO COMANDO FOR 2.
                case DATA:
                    BUFF_RESP[2] = Calendario.dia%10;
 					//BUFF_RESP[3] = Calendario.mes%10;
					//BUFF_RESP[4] = Calendario.ano%10;
					BUFF_RESP[5] = 0xFF;
					BUFF_RESP[6] = 0xFF;
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                    break;
                    
                // SE O SEGUNDO COMANDO FOR 3.
                case DESPERTADOR:
					BUFF_RESP[2] = Despertador.hora%10;
 					//BUFF_RESP[3] = Despertador.minuto%10;
					//BUFF_RESP[4] = Despertador.segundo%10;
					BUFF_RESP[5] = 0xFF;
					BUFF_RESP[6] = 0xFF;
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                    break;
			}
            break;
        
        // SE O PRIMEIRO COMANDO FOR 2. 
		case COMANDO_ALTERACAO: 
            
            BUFF_RESP[0] = BUFF_COM[0];
            BUFF_RESP[1] = BUFF_COM[1];
            BUFF_RESP[2] = BUFF_COM[2];
            BUFF_RESP[3] = BUFF_COM[3];
            BUFF_RESP[4] = BUFF_COM[4];
            
            // ANALIZA O SEGUNDO COMANDO DO TERMINAL.
         	switch(BUFF_COM[1]){  
                
                // SE O SEGUNDO COMANDO FOR 1. 
				case HORA: 
					Relogio.hora = BUFF_COM[2];
 					//Relogio.minuto = BUFF_COM[3];
					//Relogio.segundo = BUFF_COM[4];              
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                    break;
                    
                // SE O SEGUNDO COMANDO FOR 2.
                case DATA:
                    Calendario.dia = BUFF_COM[2];
 					//Calendario.mes = BUFF_COM[3];
					//Calendario.ano = BUFF_COM[4];              
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                    break;
                    
                // SE O SEGUNDO COMANDO FOR 3.
                case DESPERTADOR:
                    Despertador.hora = BUFF_COM[2];
 					//Despertador.minuto = BUFF_COM[3];
					//Despertador.segundo = BUFF_COM[4];              
					ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                    break;
			}  
            break;		
	}
}

void maquina_estado(){
    
    //gambiarra_pro_serial();
    
	switch(ESTADO_COMUNICACAO){
		case COMANDO_RECEBIDO:
            // DEPOIS DE DIGITAR 3 COMANDOs ELE PARA DE ENTRAR NO ESTADO DE ESPERA_COMANDO.
			ESTADO_COMUNICACAO = VERIFICAR_COMANDO;		
		break;

		case VERIFICAR_COMANDO:
			verifica_comando();
		break;
		
		case COMANDO_OK:
			trata_comando();
		break;

		case COMANDO_NOK:
			ESTADO_COMUNICACAO = ESPERA_COMANDO;	
		break;

		case ENVIA_RESPOSTA:
            //PORTCbits.RC0=1; // TESTE.
            //__delay_ms(180);
            //PORTCbits.RC0=0; // TESTE.
			tx_data();
			ESTADO_COMUNICACAO = ESPERA_COMANDO;
		break;

		case ESPERA_COMANDO:
		break;
	};
}

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* SERIAL_H */
