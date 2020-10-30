#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

Pessoas ler_pessoa(Pessoas lista) {
    char nome[50] = "", leitura = '\000', tipo[13] = "";
    int i = 0;

    while(leitura != '\"') {
        scanf("%c", &leitura);

        if(leitura != '\"') {
            nome[i] = leitura;
            i++;
        }
    }

    scanf(" %s", tipo);

    short preferencial = 0;
    if(strcmp(tipo, "preferencial") == 0) preferencial = 1;

    lista = pessoas_adicionar(lista, nome, preferencial);

    int prof = -1;
    while(scanf("%d ", &prof) > 0) {
        atendimentos_adicionar(lista.fim->atendimentos, prof);
    }
    
    return lista;
}

int main() {
    int profissionais[9] = {10, 2, 5, 3, 4, 7, 2, 1, 4}, i;
    Fila filas[9];
    int tempo = -1;

    for(i = 0; i < 9; i++) {
        filas[i] = fila_criar();
    }

    Pessoas pessoas = pessoas_criar();

    char leitura;
    scanf("%c", &leitura);

    while(leitura == '\"') {
        pessoas = ler_pessoa(pessoas);
        leitura = '\000';
        scanf("%c", &leitura);
    }

    while(pessoas.comeco != NULL) {
        for(i = 0; i < 9; i++) {
            int atendendo = 0;
            int max = profissionais[i];

            while(filas[i].comeco != NULL && atendendo < max) {
                filas[i] = fila_remover_comeco(filas[i]);
                atendendo++;
            }
        }

        tempo++;

        PessoasNo *pessoa = pessoas.comeco;
        while(pessoa != NULL) {
            if(pessoa->naFila == 0) {
                if(pessoa->atendimentos->comeco == NULL) {
                    int horas = tempo / 6;
                    int minutos = tempo % 6;

                    printf("%02d:%d0 %s\n", 8 + horas, minutos, pessoa->nome);
                    
                    if(pessoa->ante == NULL) {
                        pessoas.fim = pessoa->prox;
                    } else {
                        pessoa->ante->prox = pessoa->prox;
                    }

                    if(pessoa->prox == NULL) {
                        pessoas.comeco = pessoa->ante;
                    } else {
                        pessoa->prox->ante = pessoa->ante;
                    }

                    PessoasNo *removido = pessoa;
                    atendimentos_destruir(removido->atendimentos);

                    pessoa = pessoa->ante;
                    free(removido);
                } else {
                    int profissional = pessoa->atendimentos->comeco->profissional - 1;
                    if(pessoa->preferencial == 1) {
                        filas[profissional] = fila_adicionar_comeco(filas[profissional], pessoa);
                    } else {
                        filas[profissional] = fila_adicionar_fim(filas[profissional], pessoa);
                    }

                    atendimentos_remover(pessoa->atendimentos);
                    pessoa = pessoa->ante;
                }
            } else {
                pessoa = pessoa->ante;
            }
        }
    }

    for(i = 0; i < 9; i++) {
        fila_destruir(filas[i]);
    }

    pessoas_destruir(pessoas);

    return 0;
}