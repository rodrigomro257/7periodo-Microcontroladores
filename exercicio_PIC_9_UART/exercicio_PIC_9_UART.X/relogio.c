#include "relogio.h"

void tratar_relogio(relogio *Relogio, calendario *Calendario){
    
    Relogio->segundo++;
    
    if(Relogio->segundo>59){
        Relogio->minuto++;
        Relogio->segundo=0;
    }
    if(Relogio->segundo<0){
        Relogio->segundo=59;
        Relogio->minuto--;
    }
    
    if(Relogio->minuto>59){
        Relogio->hora++;
        Relogio->minuto=0;
    }
    if(Relogio->minuto<0){
        Relogio->minuto=59;
        Relogio->hora--;
    }
    
    if(Relogio->hora>23){
        Calendario->dia++;
        Relogio->hora=0;
    }    
    if(Relogio->hora<0){
        Relogio->hora=23;
        Calendario->dia--;
    }
    
    if(Calendario->dia>qtdDias_mes[Calendario->mes]){
        Calendario->mes++;
        Calendario->dia=1;
    }
    if(Calendario->dia<1){
        Calendario->mes--;
        Calendario->dia=qtdDias_mes[Calendario->mes];
    }
    
    if(Calendario->mes>12){
        Calendario->ano++;
        Calendario->mes=1;
    }
    if(Calendario->mes<1){
        Calendario->mes=12;
        Calendario->dia=qtdDias_mes[Calendario->mes];
        Calendario->ano--;
    }
    
    if(Calendario->ano>=100){
        Calendario->ano=00;
    }
    if(Calendario->ano<0){
        Calendario->ano=99;
    }
}

void controla_despertador(relogio *Despertador){
    if(Despertador->segundo>59){
        Despertador->minuto++;
        Despertador->segundo=0;
    }
    if(Despertador->segundo<0){
        Despertador->segundo=59;
        Despertador->minuto--;
    }
    
    if(Despertador->minuto>59){
        Despertador->hora++;
        Despertador->minuto=0;
    }
    if(Despertador->minuto<0){
        Despertador->minuto=59;
        Despertador->hora--;
    }
    
    if(Despertador->hora>23){
        Despertador->hora=0;
    }
    if(Despertador->hora<0){
        Despertador->hora=23;
    }
}
