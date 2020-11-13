#ifndef _ARVORE_H
#define _ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

/**
 * @brief Cria um novo nó
 * 
 * @param dado Dado desse nó
 * @param chave Chave(texto) desse nó
 * @param esq Filho da esquerda (pode ser NULL)
 * @param dir Filho da direita (pode ser NULL)
 * @return No* Nó criado
 */
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

/**
 * @brief Destrói e libera a memória de uma árvore recursivamente
 * 
 * @param raiz Raiz da árvore
 */
void destruir(No* raiz) {
    if(raiz == NULL) return;

    destruir(raiz->dir);
    destruir(raiz->esq);
    free(raiz);
}

/**
 * @brief Adiciona um novo par de dado e chave na árvore
 * 
 * @param raiz Raiz da árvore
 * @param dado Novo dado
 * @param chave Nova chave
 * @return No* Raiz da árvore com o novo dado e chave
 */
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

/**
 * @brief Remove um nó da árvore
 * 
 * @param raiz Raíz da árvore
 * @param x Nó pra remover
 * @return No* Raiz da nova árvore
 */
No* remover(No* raiz, No* x) {
    if(raiz == NULL) return NULL;

    // Recursivo até encontrar o nó
    if(x->dado > raiz->dado) {
        raiz->dir = remover(raiz->dir, x);
    } else if(x->dado < raiz->dado) {
        raiz->esq = remover(raiz->esq, x);
    } else {
        if(raiz->dir == NULL) { // Se ele não tiver filho direito
            No* temp = raiz->esq;   // O filho da esquerda irá entrar no lugar dele
            free(raiz);
            return temp;
        } else if(raiz->esq == NULL) {  // Se ele não tiver filho da esquerda
            No* temp = raiz->dir;   // O filho da direita irá entrar no lugar dele
            free(raiz);
            return temp;
        } else {    // Se ele tiver os dois filhos
            No* filho = minimo(raiz->dir);  // Encontramos o menor filho da sub-árvore direita
            raiz->dado = filho->dado;       // Trocamos de dado e chave
            strcpy(raiz->chave, filho->chave);
            raiz->dir = remover(raiz->dir, filho);  // E removemos esse menor filho
        }
    }
    
    return raiz;
}

/**
 * @brief Retorna o nó com o menor dado da árvore
 * 
 * @param raiz Raiz da árvore
 * @return No* Nó com menor dado
 */
No* minimo(No* raiz) {
    if(raiz == NULL) return NULL;
    while(raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

/**
 * @brief Retorna o nó com o maior dado da árvore
 * 
 * @param raiz Raiz da árvore
 * @return No* Nó com maior dado
 */
No* maximo(No* raiz) {
    if(raiz == NULL) return NULL;
    while(raiz->dir != NULL) raiz = raiz->dir;
    return raiz;
}

/**
 * @brief Retorna o nó que é o sucessor do nó dado
 * 
 * @param raiz Raiz da árvore
 * @param x Nó pra encontrar o sucessor
 * @return No* Sucessor do nó
 */
No* sucessor(No* raiz, No* x) {
    if(raiz == NULL) return NULL;

    if(x->dir != NULL) {    // Se ele tiver sub-árvore na direita
        return minimo(x->dir);  // Pegamos o menor dessa árvore
    }

    No* suce = NULL;

    while(raiz != NULL) {   // Caso contrário, percorremos a árvore procurando
        if(x->dado < raiz->dado) {
            suce = raiz;
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }

    return suce;
}

/**
 * @brief Retorna o nó que é o antecessor do nó dado
 * 
 * @param raiz Raiz da árvore
 * @param x Nó pra encontrar o antecessor
 * @return No* antecessor do nó
 */
No* antecessor(No* raiz, No* x) {
    if(raiz == NULL) return NULL;

    if(x->esq != NULL) {    // Se ele tiver sub-árvore na esquerda
        return maximo(x->esq);  // Retornamos o maior dessa árvore
    }

    No* ante = NULL;

    while(raiz != NULL) {   // Caso contrário, percorremos a árvore procurando
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