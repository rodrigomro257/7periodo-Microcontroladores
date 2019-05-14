#ifndef ESCOLA_H_INCLUDED
#define ESCOLA_H_INCLUDED

typedef struct{
    char nome[30];
    int matricula;
    int notas[3];
    int numero_chamada;
}Aluno;

typedef struct{
    char codigo;
    Aluno alunos[30];
}Turma;

char menu(Turma *turma, int controle_aluno);

Aluno cadastrar_aluno(int numero_chamada);
void imprimir_nome(Aluno alunos[30], int numero_chamada);
void imprimir_matricula(Aluno alunos[30], int numero_chamada);
void imprimir_notas(Aluno alunos[30], int numero_chamada);
void imprimir_todos_dados(Aluno alunos[30], int numero_chamada);
void imprimir_media_notas(Aluno alunos[30], int numero_chamada);

void imprimir_turma(Aluno *aluno, char codigo);

#endif // ESCOLA_H_INCLUDED
