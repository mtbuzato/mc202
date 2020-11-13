#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

/**
 * @brief Faz a leitura das linhas e cria uma árvore
 * 
 * @param m Número de linhas pra ler
 * @return No* Raiz da árvore criada
 */
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

/**
 * @brief Encontra os 3 nós com valores que, somados, igualam o cartão
 * 
 * @param cartao Número pra encontrar
 * @param raiz Raiz da árvore
 * @param aP Endereço onde será guardado o nó encontrado
 * @param bP Endereço onde será guardado o nó encontrado
 * @param cP Endereço onde será guardado o nó encontrado
 */
void triade(int cartao, No* raiz, No** aP, No** bP, No** cP) {
    No* a = maximo(raiz);   // Começamos com o maior número

    while(a->dado > cartao) a = antecessor(raiz, a);    // Excluímos aqueles que já são maiores que nosso cartão

    No* b = antecessor(raiz, a), *c = antecessor(raiz, b);  // Preparamos os 2 outros números

    while(a != NULL) {  // Percorremos diminuindo b e c até encontrar a soma
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

    if(a == NULL || b == NULL || c == NULL) {   // Se algum deles for NULL, não existe soma possível
        printf("Erro ao calcular token.\n");
        exit(1);
    }

    *aP = a;
    *bP = b;
    *cP = c;
}

int main() {
    int m, n;

    while(scanf("%d %d", &m, &n) > 0) { // Enquanto houver coisas pra ler
        No* raiz = ler(m);  // Fazemos a leitura e criamos a árvore

        for(int i = 0; i < n; i++) {    // Calculamos os cartões
            int cartao;

            scanf("%d ", &cartao);

            No* a = NULL, *b = NULL, *c = NULL;
            triade(cartao, raiz, &a, &b, &c);

            char token[750];    // Fazemos a soma de suas chaves(textos)
            strcpy(token, c->chave);
            strcat(token, b->chave);
            strcat(token, a->chave);

            raiz = remover(raiz, a);    // Removemos eles da árvore
            raiz = remover(raiz, b);
            raiz = remover(raiz, c);
            raiz = adicionar(raiz, cartao, token);      // Adicionamos o novo

            if(i + 1 == n) {    // Se for o último cartão, hora de encontrar a resposta
                No *percorrer = minimo(raiz);   // Começamos no menor (ordem crescente)

                while(percorrer != NULL) {  // E vamos indo de sucessor em sucessor imprimindo a resposta
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