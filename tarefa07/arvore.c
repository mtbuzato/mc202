#ifndef _ARVORE_H
#define _ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

No* criar(int dado, char *chave, No* esq, No* dir) {
    No* novo = malloc(sizeof(No));
    if(novo == NULL) {
        printf("OOM\n");
        exit(0);
    }

    novo->dado = dado;
    strcpy(novo->chave, chave);
    novo->esq = esq;
    novo->dir = dir;

    return novo;
}

void destruir(No* raiz) {
    if(raiz == NULL) return;

    destruir(raiz->dir);
    destruir(raiz->esq);
    free(raiz);
}

No* adicionar(No* raiz, int dado, char chave[]) {
    if(raiz == NULL) {
        return criar(dado, chave, NULL, NULL);
    }

    if(dado > raiz->dado) {
        raiz->dir = adicionar(raiz->dir, dado, chave);
    } else if(dado < raiz->dado) {
        raiz->esq = adicionar(raiz->esq, dado, chave);
    }

    return raiz;
}

No* remover(No* raiz, No* x) {
    if(raiz == NULL) return NULL;

    if(x->dado > raiz->dado) {
        raiz->dir = remover(raiz->dir, x);
    } else if(x->dado < raiz->dado) {
        raiz->esq = remover(raiz->esq, x);
    } else {
        if(raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        } else if(raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else {
            No* filho = minimo(raiz->dir);
            raiz->dado = filho->dado;
            strcpy(raiz->chave, filho->chave);
            raiz->dir = remover(raiz->dir, filho);
        }
    }
    
    return raiz;
}

No* minimo(No* raiz) {
    if(raiz == NULL) return NULL;
    while(raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

No* maximo(No* raiz) {
    if(raiz == NULL) return NULL;
    while(raiz->dir != NULL) raiz = raiz->dir;
    return raiz;
}

No* sucessor(No* raiz, No* x) {
    if(raiz == NULL) return NULL;

    if(x->dir != NULL) {
        return minimo(x->dir);
    }

    No* suce = NULL;

    while(raiz != NULL) {
        if(x->dado < raiz->dado) {
            suce = raiz;
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }

    return suce;
}

No* antecessor(No* raiz, No* x) {
    if(raiz == NULL) return NULL;

    if(x->esq != NULL) {
        return maximo(x->esq);
    }

    No* ante = NULL;

    while(raiz != NULL) {
        if(x->dado > raiz->dado) {
            ante = raiz;
            raiz = raiz->dir;
        } else {
            raiz = raiz->esq;
        }
    }

    return ante;
}

#endif