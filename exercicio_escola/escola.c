#include <stdio.h>
#include <stdlib.h>
#include "escola.h"

Aluno cadastrar_aluno(int numero_chamada){
    Aluno aluno;
    printf("\n------- CADASTRO DE ALUNO -------\n\n");
    printf(" Nome: ");
    scanf("%s", &aluno.nome);
    printf(" Numero matricula: ");
    scanf("%d", &aluno.matricula);
    printf(" Nota 1: ");
    scanf("%d", &aluno.notas[0]);
    printf(" Nota 2: ");
    scanf("%d", &aluno.notas[1]);
    printf(" Nota 3: ");
    scanf("%d", &aluno.notas[2]);
    aluno.numero_chamada=numero_chamada+1;
    printf("\n Aluno %s cadastrado com sucesso.\n Seu numero de chamada e %d.\n", aluno.nome, aluno.numero_chamada);
    return aluno;
}

void imprimir_nome(Aluno alunos[30], int numero_chamada){
    printf("\n O aluno de numero de chamada %d se chama %s.\n", numero_chamada, alunos[numero_chamada-1].nome);
}

void imprimir_matricula(Aluno alunos[30], int numero_chamada){
    printf("\n O aluno de numero de chamada %d possui matricula %d.\n", numero_chamada, alunos[numero_chamada-1].matricula);
}

void imprimir_notas(Aluno alunos[30], int numero_chamada){
    printf("\n O aluno de numero de chamada %d possui as notas:\n N1: %d.\n N2: %d.\n N3: %d.\n", numero_chamada, alunos[numero_chamada-1].notas[0], alunos[numero_chamada-1].notas[1], alunos[numero_chamada-1].notas[2]);
}

void imprimir_todos_dados(Aluno alunos[30], int numero_chamada){
    printf("\n O aluno de numero de chamada %d possui os seguintes dados:\n Nome: %s.\n Matricula: %d.\n N1: %d.\n N2: %d.\n N3: %d.\n\n", numero_chamada, alunos[numero_chamada-1].nome, alunos[numero_chamada-1].matricula, alunos[numero_chamada-1].notas[0], alunos[numero_chamada-1].notas[1], alunos[numero_chamada-1].notas[2]);
}

void imprimir_media_notas(Aluno alunos[30], int numero_chamada){
    double media=((alunos[numero_chamada-1].notas[0]+alunos[numero_chamada-1].notas[1]+alunos[numero_chamada-1].notas[2])/2);
    printf("\n O aluno de numero de chamada %d possui media de notas %f\n", numero_chamada, media);
}

char menu(Turma *turma, int controle_aluno){
    char opcao;
    int numero_chamada=0;
    printf("\n\n------- MENU -------\n\n 1. Cadastrar aluno.\n 2. Imprimir nome.\n 3. Imprimir matricula.\n 4. Imprimir notas.\n 5. Imprimir todos dados.\n 6. Imprimir media notas.\n 0. Finalizar sistema.\n");
    printf("\n Qual operacao deseja efetuar? ");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
            if(controle_aluno>=30) printf("\n\n TURMA CHEIA.\n\n");
            else turma->alunos[controle_aluno]=cadastrar_aluno(controle_aluno);
            break;
        case 2:
            printf("\n Deseja consultar o nome do aluno com qual numero de chamada? ");
            scanf("%d", &numero_chamada);
            if(numero_chamada>controle_aluno) printf("\n Aluno nao cadastrado.");
            else imprimir_nome(turma->alunos, numero_chamada);
            break;
        case 3:
            printf("\n Deseja consultar a matricula do aluno com qual numero de chamada? ");
            scanf("%d", &numero_chamada);
            if(numero_chamada>controle_aluno) printf("\n Aluno nao cadastrado.");
            else imprimir_matricula(turma->alunos, numero_chamada);
            break;
        case 4:
            printf("\n Deseja consultar as notas do aluno com qual numero de chamada? ");
            scanf("%d", &numero_chamada);
            if(numero_chamada>controle_aluno) printf("\n Aluno nao cadastrado.");
            else imprimir_notas(turma->alunos, numero_chamada);
            break;
        case 5:
            printf("\n Deseja consultar os dados do aluno com qual numero de chamada? ");
            scanf("%d", &numero_chamada);
            if(numero_chamada>controle_aluno) printf("\n Aluno nao cadastrado.");
            else imprimir_todos_dados(turma->alunos, numero_chamada);
            break;
        case 6:
            printf("\n Deseja consultar a media das notas do aluno com qual numero de chamada? ");
            scanf("%d", &numero_chamada);
            if(numero_chamada>controle_aluno) printf("\n Aluno nao cadastrado.");
            else imprimir_media_notas(turma->alunos, numero_chamada);
            break;
        case 0:
            return 0;
        default:
            printf("\n Opcao invalida.\n\n");
    }
    return opcao;
}
