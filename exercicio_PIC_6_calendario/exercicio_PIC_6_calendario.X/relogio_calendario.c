#include "relogio_calendario.h"

void verifica_b(int ano){
    if(ano%4==0){
        qtdDias_mes[1]=29;
    }else{
        qtdDias_mes[1]=28;
    }
}

void tratar_relogio(calendario *c, relogio *r){
    r->segundo++;
    
    if(r->segundo>59){
        r->minuto++;
        r->segundo=0;
    }
    if(r->minuto>59){
        r->hora++;
        r->minuto=0;
    }
    if(r->hora>23){
        c->dia++;
        r->hora=0;
    }
    if(c->dia>qtdDias_mes[c->mes-1]){
        c->mes++;
        c->dia=1;
    }
    if(c->mes>12){
        c->ano++;
        c->mes=1;
        verifica_b(c->ano);
    }
}
