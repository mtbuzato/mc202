#include <stdlib.h>
#include <stdio.h>

#include "arvore.h"

/**
 * @brief Calcula o número mínimo de números pra remover pra lista se tornar legal
 * 
 * @param raiz Raiz da árvore
 * @return int Mínimo de números
 */
int calcular(No* raiz) {
    int total = 0;
    if(raiz != NULL) {
        if(raiz->chave < raiz->ocorrencias) {
            total += raiz->ocorrencias - raiz->chave;
        } else if(raiz->chave > raiz->ocorrencias) {
            total += raiz->ocorrencias;
        }

        total += calcular(raiz->esq);
        total += calcular(raiz->dir);
    }

    return total;
}

int main() {
    int n, k;
    No* raiz = NULL;

    scanf("%d %d", &n, &k);

    for(int i = 0; i < n; i++) {    // Cria a árvore
        int chave;

        scanf("%d ", &chave);

        raiz = adicionar(raiz, chave);
    }

    for(int i = 0; i < k; i++) {    // Lê os comandos
        int comando;

        scanf("%d ", &comando);

        if(comando < 3) {       // Se for 1 ou 2, lê o argumento
            int argumento;

            scanf("%d ", &argumento);

            if(comando == 1) {
                raiz = adicionar(raiz, argumento);
            } else {
                No* encontrado = encontrar(raiz, argumento);
                if(encontrado == NULL) {
                    printf("0\n");
                } else {
                    printf("%d\n", encontrado->ocorrencias);
                }
            }
        } else {        // Caso contrário só calcula
            printf("%d\n", calcular(raiz));
        }
    }

    destruir(raiz);

    return 0;
}