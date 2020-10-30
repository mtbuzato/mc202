#ifndef _PESSOA_H
#define _PESSOA_H

#include "pessoa.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Pessoas pessoas_criar() {
    Pessoas nova;
    nova.comeco = NULL;
    nova.fim = NULL;
    return nova;
}

Pessoas pessoas_adicionar(Pessoas lista, char nome[], short preferencial) {
    PessoasNo *novo = malloc(sizeof(PessoasNo));
    if(novo == NULL) {
        printf("OOM");
        exit(0);
    }

    if(lista.fim != NULL) {
        lista.fim->ante = novo;
    } else {
        lista.comeco = novo;
    }

    strcpy(novo->nome, nome);
    novo->preferencial = preferencial;
    novo->naFila = 0;
    novo->atendimentos = atendimentos_criar();
    novo->prox = lista.fim;
    novo->ante = NULL;

    lista.fim = novo;

    return lista;
}

Pessoas pessoas_remover(Pessoas lista) {
    if(lista.comeco == NULL) return lista;

    PessoasNo *removido = lista.comeco;

    lista.comeco = removido->ante;
    if(lista.comeco == NULL) lista.fim = NULL;

    atendimentos_destruir(removido->atendimentos);
    free(removido);

    return lista;
}

void pessoas_destruir(Pessoas lista) {
    while(lista.comeco != NULL) {
        lista = pessoas_remover(lista);
    }
}

ListaAtendimentos * atendimentos_criar() {
    ListaAtendimentos * nova = malloc(sizeof(ListaAtendimentos));
    nova->comeco = NULL;
    nova->fim = NULL;
    return nova;
}

void atendimentos_adicionar(ListaAtendimentos *lista, int profissional) {
    ListaAtendimentosNo *novo = malloc(sizeof(ListaAtendimentosNo));
    if(novo == NULL) {
        printf("OOM");
        exit(0);
    }

    if(lista->fim != NULL) {
        lista->fim->ante = novo;
    } else {
        lista->comeco = novo;
    }

    novo->profissional = profissional;
    novo->prox = lista->fim;
    novo->ante = NULL;

    lista->fim = novo;
}

void atendimentos_remover(ListaAtendimentos *lista) {
    if(lista->comeco == NULL) return;

    ListaAtendimentosNo *removido = lista->comeco;

    lista->comeco = removido->ante;
    if(lista->comeco == NULL) lista->fim = NULL;

    free(removido);
}

void atendimentos_destruir(ListaAtendimentos *lista) {
    while(lista->comeco != NULL) {
        atendimentos_remover(lista);
    }

    free(lista);
}

#endif