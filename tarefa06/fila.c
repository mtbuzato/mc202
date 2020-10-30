#ifndef _FILA_H
#define _FILA_H

#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

Fila fila_adicionar_comeco(Fila fila, PessoasNo *pessoa) {
    FilaNo *novo = malloc(sizeof(FilaNo));
    if(novo == NULL) {
        printf("OOM");
        exit(0);
    }

    if(fila.comeco != NULL) {
        fila.comeco->prox = novo;
    } else {
        fila.fim = novo;
    }

    pessoa->naFila = 1;
    
    novo->pessoa = pessoa;
    novo->prox = NULL;
    novo->ante = fila.comeco;

    fila.comeco = novo;

    return fila;
}

Fila fila_remover_comeco(Fila fila) {
    if(fila.comeco == NULL) return fila;

    FilaNo *removido = fila.comeco;
    removido->pessoa->naFila = 0;

    fila.comeco = removido->ante;
    if(fila.comeco == NULL) fila.fim = NULL;

    free(removido);

    return fila;
}

Fila fila_adicionar_fim(Fila fila, PessoasNo *pessoa) {
    FilaNo *novo = malloc(sizeof(FilaNo));
    if(novo == NULL) {
        printf("OOM");
        exit(0);
    }

    if(fila.fim != NULL) {
        fila.fim->ante = novo;
    } else {
        fila.comeco = novo;
    }

    pessoa->naFila = 1;

    novo->pessoa = pessoa;
    novo->prox = fila.fim;
    novo->ante = NULL;

    fila.fim = novo;

    return fila;
}

Fila fila_remover_fim(Fila fila) {
    if(fila.fim == NULL) return fila;

    FilaNo *removido = fila.fim;
    removido->pessoa->naFila = 0;

    fila.fim = removido->prox;
    if(fila.fim == NULL) fila.comeco = NULL;

    free(removido);

    return fila;
}

Fila fila_criar() {
    Fila fila;
    fila.comeco = NULL;
    fila.fim = NULL;
    return fila;
}

void fila_destruir(Fila fila)  {
    while(fila.comeco != NULL) {
        fila = fila_remover_comeco(fila);
        if(fila.comeco != NULL) fila = fila_remover_fim(fila);
    }
}

#endif