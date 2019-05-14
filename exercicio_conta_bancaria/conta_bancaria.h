#ifndef CONTA_BANCARIA_H_INCLUDED
#define CONTA_BANCARIA_H_INCLUDED

typedef struct{
    int numero;
    int valor;
} conta_bancaria;

void inicializar(conta_bancaria *conta, int numero, int valor);
void sacar(conta_bancaria *conta, int valor);
void depositar(conta_bancaria *conta, int valor);
void imprimir(conta_bancaria *conta);

char menu(conta_bancaria *conta);

#endif // CONTA_BANCARIA_H_INCLUDED
