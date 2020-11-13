#ifndef _ARVORE_H
#define _ARVORE_H

#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

// Decidi utilizar árvores AVL pois são melhores para buscas

/**
 * @brief Retorna o maior dos dois inteiros
 * 
 * @param a Inteiro A
 * @param b Inteiro B
 * @return int maior inteiro
 */
int max(int a, int b) {
    if(a > b) return a;
    return b;
}

/**
 * @brief Cria um novo nó de árvore
 * 
 * @param chave Chave pra criar o nó
 * @return No* Nó criado
 */
No* criar(int chave) {
    No* no = malloc(sizeof(No));
    if(no == NULL) {
        printf("OOM\n");
        exit(1);
    }

    no->chave = chave;
    no->ocorrencias = 1;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;

    return no;
}

/**
 * @brief Destrói uma árvore inteira, liberando memória
 * 
 * @param raiz Raiz da árvore para destruir
 */
void destruir(No* raiz) {
    if(raiz == NULL) return;

    destruir(raiz->esq);
    destruir(raiz->dir);
    free(raiz);
}

/**
 * @brief Retorna a altura do nó se preocupando com NULLs
 * 
 * @param x Nó pra verificar a altura
 * @return int Altura do nó
 */
int altura(No* x) {
    if(x == NULL) return 0;
    return x->altura;
}

/**
 * @brief Roda a sub-árvore AVL pra direita, pra manter o balanço
 * 
 * @param x Raiz da sub-árvore pra rodar
 * @return No* Nova raiz
 */
No* rodarPraDireita(No* x) {
    No* eixo = x->esq;
    No* filho = eixo->dir;

    eixo->dir = x;
    x->esq = filho;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    eixo->altura = max(altura(eixo->esq), altura(eixo->dir)) + 1;

    return eixo;
}

/**
 * @brief Roda a sub-árvore AVL pra esquerda, pra manter o balanço
 * 
 * @param x Raiz da sub-árvore pra rodar
 * @return No* Nova raiz
 */
No* rodarPraEsquerda(No* x) {
    No* eixo = x->dir;
    No* filho = eixo->esq;

    eixo->esq = x;
    x->dir = filho;

    x->altura = max(altura(x->esq), altura(x->dir)) + 1;
    eixo->altura = max(altura(eixo->esq), altura(eixo->dir)) + 1;

    return eixo;
}

/**
 * @brief Retorna o balanço dos filhos do nó
 * 
 * @param x Nó pra retornar o balanço
 * @return int Balanço dos filhos
 */
int balanco(No* x) {
    if(x == NULL) return 0;
    return altura(x->esq) - altura(x->dir);
}

/**
 * @brief Recursivamente insere uma nova chave na árvore com base na raiz, mantendo-a balançeada
 * 
 * @param raiz Raiz da árvore ou sub-árvore
 * @param chave Chave pra adicionar
 * @return No* Nova raiz
 */
No* adicionar(No* raiz, int chave) {
    if(raiz == NULL) return criar(chave);

    if(chave > raiz->chave) {
        raiz->dir = adicionar(raiz->dir, chave);
    } else if(chave < raiz->chave) {
        raiz->esq = adicionar(raiz->esq, chave);
    } else {
        raiz->ocorrencias++;
        return raiz; // Não aceitamos duplicados
    }

    // Atualizando altura
    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    // Calcula o balanço
    int bal = balanco(raiz);

    // Se estiver desbalanceado, precisamos tratar um dos 4 casos

    if(bal > 1) {
        if(chave < raiz->esq->chave) {      // Tipo Esquerda-Esquerda
            return rodarPraDireita(raiz);
        } else if(chave > raiz->esq->chave) {       // Tipo Esquerda-Direita
            raiz->esq = rodarPraEsquerda(raiz->esq);
            return rodarPraDireita(raiz);
        }
    } else if(bal < -1) {
        if(chave > raiz->dir->chave) {      // Tipo Direita-Direita
            return rodarPraEsquerda(raiz);
        } else if(chave < raiz->dir->chave) {       // Tipo Direita-Esquerda
            raiz->dir = rodarPraDireita(raiz->dir);
            return rodarPraEsquerda(raiz);
        }
    }

    return raiz;
}

/**
 * @brief Encontra um nó com base na chave
 * 
 * @param raiz Raiz da árvore
 * @param chave Chave pra encontrar
 * @return No* Nó encontrado ou NULL se não encontrado
 */
No* encontrar(No* raiz, int chave) {
    if(raiz == NULL) return NULL;

    if(chave > raiz->chave) {
        return encontrar(raiz->dir, chave);
    } else if(chave < raiz->chave) {
        return encontrar(raiz->esq, chave);
    } else {
        return raiz;
    }
}

#endif