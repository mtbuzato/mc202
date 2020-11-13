#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

No* ler(int m) {
    No* raiz = NULL;

    for(int i = 0; i < m; i++) {
        int dado;
        char texto[5];

        scanf("%d ", &dado);
        scanf("\"%[^\"]\"", texto);

        raiz = adicionar(raiz, dado, texto);
    }

    return raiz;
}

void triade(int cartao, No* raiz, No** aP, No** bP, No** cP) {
    No* a = maximo(raiz);

    while(a->dado > cartao) a = antecessor(raiz, a);

    No* b = antecessor(raiz, a), *c = antecessor(raiz, b);

    while(a != NULL) {
        while(b != NULL) {
            while(c != NULL) {
                if(a->dado + b->dado + c->dado != cartao) {
                    c = antecessor(raiz, c);
                } else {
                    break;
                }
            }

            if(c == NULL) {
                b = antecessor(raiz, b);
                if(b != NULL) c = antecessor(raiz, b);
            } else {
                break;
            }
        }

        if(b == NULL) {
            a = antecessor(raiz, a);
            if(a != NULL) b = antecessor(raiz, a);
            if(b != NULL) c = antecessor(raiz, b);
        } else {
            break;
        }
    }

    if(a == NULL || b == NULL || c == NULL) {
        printf("Erro ao calcular token.\n");
        exit(1);
    }

    *aP = a;
    *bP = b;
    *cP = c;
}

int main() {
    int m, n;

    while(scanf("%d %d", &m, &n) > 0) {
        No* raiz = ler(m);

        for(int i = 0; i < n; i++) {
            int cartao;

            scanf("%d ", &cartao);

            No* a = NULL, *b = NULL, *c = NULL;
            triade(cartao, raiz, &a, &b, &c);

            char token[750];
            strcpy(token, c->chave);
            strcat(token, b->chave);
            strcat(token, a->chave);

            raiz = remover(raiz, a);
            raiz = remover(raiz, b);
            raiz = remover(raiz, c);
            raiz = adicionar(raiz, cartao, token);

            if(i + 1 == n) {
                No *percorrer = minimo(raiz);

                while(percorrer != NULL) {
                    printf("%s", percorrer->chave);
                    percorrer = sucessor(raiz, percorrer);
                }

                printf("\n");

                destruir(raiz);
            }
        }
    }

    return 0;
}