#ifndef PROFESSOR_CARLOS_H
#define PROFESSOR_CARLOS_H

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct aluno {
    Data nascimento;
    char nome[15];
    char sobrenome[15];
} Aluno;

typedef struct turma {
    Aluno alunos[50];
    int qtd;
} Turma;

// Função para comparar datas
// Retorna 1 se a > b, -1 se a < b, e 0 se a = b
int compararDatas(Data a, Data b);

// Função para comparar strings
// Retorna 1 se a > b, -1 se a < b, e 0 se a = b (ordem alfabética)
int compararStr(char a[], char b[]);

// Função para comparar nome de alunos
// Retorna 1 se a > b, -1 se a < b, e 0 se a = b (ordem alfabética de nome e sobrenome)
int ordemAlfabetica(Aluno a, Aluno b);

// Dados a e b, retorna o mais novo (0 = a, 1 = b)
int maisNovo(Aluno a, Aluno b);

// Dados a e b, retorna o mais velho (0 = a, 1 = b)
int maisVelho(Aluno a, Aluno b);

// Função para medir tamanho de strings
int tamanho(char str[]);

// Função para encontrar onde na string ocorre uma substring
int indexOf(char str[], char search[]);

// A funcao recebe todas as turma e a turma escolhida,
// retornando o aluno mais novo da turma escolhida.
Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j);

// A funcao recebe todas as turmas e retorna o aluno mais novo dentre todas as turmas.
Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas);

// A funcao recebe todas as turma e o indice da turma escolhida,
// retornando o aluno mais velho da turma escolhida.
Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j);

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas);
// A funcao recebe todas as turmas e retorna o aluno mais velho dentre todas as turmas.

// A funcao recebe todoas as turmas e uma string,
// retornando a quantidade de alunos que a string aparece em seu nome.
int conta_substrings(Turma t[], int qtd_turmas, char *padrao);

// Adiciona o aluno A na turma j, retornando a quantidade de alunos da turma j.
int add_aluno(Turma t[], Aluno A, int j);

// Remove o ultimo aluno adicionado na turma j,
// retornando a quantidade de alunos restante na turma j.
int remove_aluno(Turma t[], int j);

#endif
