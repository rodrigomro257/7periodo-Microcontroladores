#include "display.h"

int variavel_exibida=0; // CONTROLA QUE VARI�VEL SER� EXIBIDA.

void controlador_variavel_display(relogio *re, calendario *ca){
    
    /*
    // EXIBIR SEGUNDO.
    if(variavel_exibida==0){
        PORTC=display[(re->segundo)%10];
        PORTB=display[((re->segundo)/10)-(((re->segundo)%10)/10)]; 
    }
    
    // EXIBIR MINUTO.
    if(variavel_exibida==1){
        PORTC=display[(re->minuto)%10];
        PORTB=display[((re->minuto)/10)-(((re->minuto)%10)/10)];
    }
    
    // EXIBIR HORA.
    if(variavel_exibida==2){
        PORTC=display[(re->hora)%10];
        PORTB=display[((re->hora)/10)-(((re->hora)%10)/10)];
    }
    
    // EXIBIR DIA.
    if(variavel_exibida==3){
        PORTC=display[(ca->dia)%10];
        PORTB=display[((ca->dia)/10)-(((ca->dia)%10)/10)];
    }
    
    // EXIBIR M�S.
    if(variavel_exibida==4){
        PORTC=display[(ca->mes)%10];
        PORTB=display[((ca->mes)/10)-(((ca->mes)%10)/10)];
    }
    
    // EXIBIR ANO.
    if(variavel_exibida==5){
        PORTC=display[(ca->ano)%10];
        PORTB=display[((ca->ano)/10)-(((ca->ano)%10)/10)];
    }
    */
    
    
    // EXIBIR QUAL VARI�VEL EST� SENDO MOSTRADA.
    PORTA=display[variavel_exibida];
    
    // EXIBIR SEGUNDO.
    if(variavel_exibida==0){
        PORTDbits.RD3=1; // LIGA TRANSISTOR DIREITA.
        PORTB=display[(re->segundo)%10];
        __delay_ms(180); 
        //PORTDbits.RD3=0; // DESLIGA TRANSISTOR DIREITA.
        
        PORTDbits.RD2=1; // LIGA TRANSISTOR ESQUERDA.
        PORTB=display[((re->segundo)/10)-(((re->segundo)%10)/10)];
        __delay_ms(180); 
        PORTDbits.RD2=0; // DESLIGA TRANSISTOR ESQUERDA. 
    }
    
    // EXIBIR MINUTO.
    if(variavel_exibida==1){
        PORTDbits.RD3=1; // LIGA TRANSISTOR DIREITA.
        PORTB=display[(re->minuto)%10];
        __delay_ms(180); 
        PORTDbits.RD3=0; // DESLIGA TRANSISTOR DIREITA.
        
        PORTDbits.RD2=1; // LIGA TRANSISTOR ESQUERDA.
        PORTB=display[((re->minuto)/10)-(((re->minuto)%10)/10)];
        __delay_ms(180); 
        PORTDbits.RD2=0; // DESLIGA TRANSISTOR ESQUERDA. 
    }
    
    // EXIBIR HORA.
    if(variavel_exibida==2){
        PORTDbits.RD3=1; // LIGA TRANSISTOR DIREITA.
        PORTB=display[(re->hora)%10];
        __delay_ms(180); 
        PORTDbits.RD3=0; // DESLIGA TRANSISTOR DIREITA.
        
        PORTDbits.RD2=1; // LIGA TRANSISTOR ESQUERDA.
        PORTB=display[((re->hora)/10)-(((re->hora)%10)/10)];
        __delay_ms(180); 
        PORTDbits.RD2=0; // DESLIGA TRANSISTOR ESQUERDA. 
    }
    
    // EXIBIR DIA.
    if(variavel_exibida==3){
        PORTDbits.RD3=1; // LIGA TRANSISTOR DIREITA.
        PORTB=display[(ca->dia)%10];
        __delay_ms(180); 
        PORTDbits.RD3=0; // DESLIGA TRANSISTOR DIREITA.
        
        PORTDbits.RD2=1; // LIGA TRANSISTOR ESQUERDA.
        PORTB=display[((ca->dia)/10)-(((ca->dia)%10)/10)];
        __delay_ms(180); 
        PORTDbits.RD2=0; // DESLIGA TRANSISTOR ESQUERDA. 
    }
    
    // EXIBIR M�S.
    if(variavel_exibida==4){
        PORTDbits.RD3=1; // LIGA TRANSISTOR DIREITA.
        PORTB=display[(ca->mes)%10];
        __delay_ms(180); 
        PORTDbits.RD3=0; // DESLIGA TRANSISTOR DIREITA.
        
        PORTDbits.RD2=1; // LIGA TRANSISTOR ESQUERDA.
        PORTB=display[((ca->mes)/10)-(((ca->mes)%10)/10)];
        __delay_ms(180); 
        PORTDbits.RD2=0; // DESLIGA TRANSISTOR ESQUERDA. 
    }
    
    // EXIBIR ANO.
    if(variavel_exibida==5){
        PORTDbits.RD3=1; // LIGA TRANSISTOR DIREITA.
        PORTB=display[(ca->ano)%10];
        __delay_ms(180); 
        PORTDbits.RD3=0; // DESLIGA TRANSISTOR DIREITA.
        
        PORTDbits.RD2=1; // LIGA TRANSISTOR ESQUERDA.
        PORTB=display[((ca->ano)/10)-(((ca->ano)%10)/10)];
        __delay_ms(180); 
        PORTDbits.RD2=0; // DESLIGA TRANSISTOR ESQUERDA. 
    }
    
    /*
    // TESTES ANTIGOS.
    if(variavel_exibida==0) PORTB=display[re->segundo];
    if(variavel_exibida==1) PORTB=display[re->minuto];
    if(variavel_exibida==2) PORTB=display[re->hora];
    if(variavel_exibida==3) PORTB=display[ca->dia];
    if(variavel_exibida==4) PORTB=display[ca->mes];
    if(variavel_exibida==5) PORTB=display[ca->ano];
    PORTA=display[variavel_exibida]; 
     */
}

void checa_botao_pressionado(relogio *re, calendario *ca){
    // TROCA VARI�VEL EXIBIDA.
    // AO PRESSIONAR O BOT�O 1 A EXIBI��O � DIRECIONADA PARA OUTRA VARI�VEL.
    if(PORTDbits.RD0==1){
        __delay_ms(180); 
        variavel_exibida++;
        while(PORTDbits.RD0==1){}
    }
    if(variavel_exibida>5) variavel_exibida=0;
    
    // INCREMENTA VARI�VEL EXIBIDA.
    // AO PRESSIONAR O BOT�O 2 A VARI�VEL EXIBIDA � INCREMENTADA.
    if(PORTDbits.RD1==1){
        __delay_ms(180);
        if(variavel_exibida==0){
            re->segundo++;
            if(re->segundo==60) re->segundo=0;
        }
        if(variavel_exibida==1){
            re->minuto++;
            if(re->minuto==60) re->minuto=0;
        }
        if(variavel_exibida==2){
            re->hora++;
            if(re->hora==24) re->hora==0;
        }
        if(variavel_exibida==3){
            ca->dia++;
        }
        if(variavel_exibida==4){
            ca->mes++;
            if(ca->mes==13){
                ca->mes=1;
                ca->ano++;
            } 
        }
        if(variavel_exibida==5){
            ca->ano++;
        }
    }
    
    /*
    if(PORTDbits.RD0==1) variavel_exibida++;
    //if(PORTDbits.RD0==1) re->segundo=0;
    if(variavel_exibida>5) variavel_exibida=0;
    
    // AO PRESSIONAR O BOT�O 2 A VARI�VEL EXIBIDA � INCREMENTADA.
    if(PORTDbits.RD1==1 && variavel_exibida==0) re->segundo++;
    if(PORTDbits.RD1==1 && variavel_exibida==1) re->minuto++;
    if(PORTDbits.RD1==1 && variavel_exibida==2) re->hora++;
    if(PORTDbits.RD1==1 && variavel_exibida==3) ca->dia++;
    if(PORTDbits.RD1==1 && variavel_exibida==4) ca->mes++;
    if(PORTDbits.RD1==1 && variavel_exibida==5) ca->ano++; 
     */
}
