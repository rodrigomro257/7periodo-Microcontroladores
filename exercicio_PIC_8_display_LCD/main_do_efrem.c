/*
 * File:   main.c
 * Author: Marco
 *
 * Created on 12 de Abril de 2018, 13:20
 */




//#include "relogio.h"

#include <xc.h> // include processor files - each processor file is guarded.  
#include <plib/usart.h>
#include <p18f4550.h>
#include <xlcd.h>
#include <delays.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POLY 0x8408
#define _XTAL_FREQ 12000000



#pragma config PBADEN = OFF 
#pragma config WDT = OFF






void DelayFor18TCY(void){
    Delay10TCYx(120);
}
 
void DelayPORXLCD(void){
    Delay1KTCYx(180);
    return;
}
 
void DelayXLCD(void){
    Delay1KTCYx(60);
    return;

}



void init_XLCD(VOID){
    OpenXLCD(FOUR_BIT&LINES_5X7);
    while (BusyXLCD());
    WriteCmdXLCD(0x06);
    WriteCmdXLCD(0x0C);
}




/*

 * 
char verificaAnoBissexto(int ano){
    if(ano % 4 == 0 ){
        if( ano % 100 != 0){
            return 1;
        }
        else 
        {
            if( ano % 400 != 0){   
                 return 0;
            }
            else{
                return 1;
            }
        } 
    }
    else{
        return 0;
    }
          
    
}

char *converteAnoString(int ano){
    char anoStr[4];
    sprintf(anoStr,"%i",ano);
    return anoStr;
}


char verificaAnoBissexto(int ano){
    if(ano % 4 == 0 ){
        if( ano % 100 != 0){
            return 1;
        }
        else 
        {
            if( ano % 400 != 0){   
                 return 0;
            }
            else{
                return 1;
            }
        } 
    }
    else{
        return 0;
    }
          
    
}

char *converteAnoString(int ano){
    char anoStr[4];
    sprintf(anoStr,"%i",ano);
    return anoStr;
}


 * 
 * 
unsigned short crc16(char *data_p, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8;
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}
//envia buffer de resposta pela serial


void calculaCRCBUFFRESP(){
	
	unsigned short crc;
    
    crc =  crc16(BUFFRESP,5);
    
	BUFFRESP[5] = crc >> 8;
	BUFFRESP[6] = crc & 0xFF;
            
	estado = ENVIARESPOSTA;
}

void verificaCRCBUFFCOM(){
	
	//ajudar no entendimento, deve ser retirado depois
	char CRC_OK =0;
	unsigned short crc, crc1, crc2;

	crc =  crc16(BUFFCOM,5);
	crc1 = crc >> 8;
	crc2 = crc & 0xFF;

	if(BUFFCOM[5] == crc1 && BUFFCOM[6] == crc2){
		CRC_OK = 1;
	}

	
	
	//indica que CRC esta correto
	if (CRC_OK == 1)
	{
		estado = ENVIAACK;	
	}
	else{
		
		//CRC nao esta correto
		estado = ENVIANACK;
			
	}
		
}

*/

void main(void) {

      TRISB = 0x00;
      TRISD = 0x00;
           // To enable continuous reception
   

      
     
     init_XLCD();
     
      
     
             SetDDRamAddr(0x00);
          putrsXLCD("Efrem 2    ");
          SetDDRamAddr(0x40);
          putrsXLCD("Lousada ");
         
     
     
    while(1){
    

        
    }
    return;
}

