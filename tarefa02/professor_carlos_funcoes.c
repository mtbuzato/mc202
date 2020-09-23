#include "professor_carlos.h"

int compararDatas(Data a, Data b)  {
    if(a.ano != b.ano) {
        if(a.ano > b.ano) return 1; 
        else return -1;
    }

    if(a.mes != b.mes) {
        if(a.mes > b.mes) return 1;
        else return -1;
    }
    
    if(a.dia != b.dia) {
        if(a.dia > b.dia) return 1;
        else return -1;
    }

    return 0;
}

int compararStr(char a[], char b[], int sizeA, int sizeB)  {
    int toUse = sizeB;
    if(sizeA > sizeB) toUse = sizeA;

    for(int i = 0; i < toUse; i++) {
        if(a[i] > b[i]) return 1;
        else if(a[i] < b[i]) return -1;
    }

    if(sizeA > sizeB) return 1;
    else if(sizeB > sizeA) return -1;

    return 0;
}

int compararAlunos(Aluno a, Aluno b) {
    int comp = compararDatas(a.nascimento, b.nascimento);
    if(comp == 0) {;
        comp = compararStr(a.nome, b.nome, 14, 14);
    }

    if(comp == 0) {
        comp = compararStr(a.sobrenome, b.sobrenome, 14, 14);
    }

    return comp;
}

int tamanho(char str[]) {
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
}

int indexOf(char str[], char search[]) {
    int tamanhoSearch = tamanho(search);

    for(int i = 0; i < tamanho(str); i++) {
        if(str[i] == search[0]) {
            int n, m = 0;

            for(n = 0; n < tamanhoSearch; n++) {
                if(str[i + n] != search[n]) {
                    break;
                }
                m++;
            }

            if(m == tamanhoSearch) {
                return i;
            }
        }
    }

    return -1;
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j) {
    Aluno novo;
    Turma turma = t[j];

    for(int n = 0; n < turma.qtd; n++) {
        Aluno aluno = turma.alunos[n];

        if(n == 0) novo = aluno;
        else if(compararAlunos(novo, aluno) < 0) {
            novo = aluno;
        }

    }

    return novo;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas) {
    Aluno novo;

    for(int i = 0; i < qtd_turmas; i++) {
        Aluno aluno = procura_novo_na_turma(t, qtd_turmas, i);
        if(compararAlunos(novo, aluno) < 0) {
            novo = aluno;
        }
    }

    return novo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j) {
    Aluno velho;
    Turma turma = t[j];

    for(int n = 0; n < turma.qtd; n++) {
        Aluno aluno = turma.alunos[n];

        if(n == 0) velho = aluno;
        else if(compararAlunos(velho, aluno) > 0) {
            velho = aluno;
        }

    }

    return velho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas) {
    Aluno velho;

    for(int i = 0; i < qtd_turmas; i++) {
        Aluno aluno = procura_velho_na_turma(t, qtd_turmas, i);
        if(compararAlunos(velho, aluno) > 0) {
            velho = aluno;
        }
    }

    return velho;
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao) {
    int amount = 0;

    for(int i = 0; i < qtd_turmas; i++) {
        Turma turma = t[i];

        for(int n = 0; n < turma.qtd; n++) {
            Aluno aluno = turma.alunos[n];

            if(indexOf(aluno.nome, padrao) != -1) {
                amount++;
            }
        }
    }

    return amount;
}

int add_aluno(Turma t[], Aluno A, int j) {
    t[j].alunos[t[j].qtd] = A;
    t[j].qtd++;
    return t[j].qtd;
}

int remove_aluno(Turma t[], int j) {
    int novaQtd = t[j].qtd - 1;
    t[j].qtd = novaQtd;
    return novaQtd;
}