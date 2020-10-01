#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_item {
    char *topico;
    double *relevancias;
    double max;
    double min;
    double med;
    double dp;
} item;

typedef struct s_classificacao {
    item **itens;
    int total;
} classificacao;

int main() {
    int i, x, n, m;
    item *itens;
    classificacao *classificacoes = malloc(5 * sizeof(classificacao));

    scanf("%d %d", &n, &m);

    for(i = 0; i < 5; i++) {
        classificacoes[i].total = 0;
        classificacoes[i].itens = malloc(n * sizeof(item *));
    }

    itens = malloc(n * sizeof(item));
    for(i = 0; i < n; i++) {
        item atual = itens[i];

        atual.topico = malloc(25 * sizeof(char));
        atual.relevancias = malloc(m * sizeof(double));
        atual.max = 0.0;
        atual.min = 100.0;
        atual.med = 0;
        atual.dp = 0;

        scanf("%s ", atual.topico);
        for(x = 0; x < m; x++) {
            double relevancia = 0.0;
            scanf(" %lf", &relevancia);

            atual.relevancias[x] = relevancia;
            if(relevancia > atual.max) {
                atual.max = relevancia;
            }
            
            if(relevancia < atual.min) {
                atual.min = relevancia;
            }
        }

        double total = 0.0;
        for(x = 0; x < m; x++) {
            total += atual.relevancias[x];
        }
        atual.med = total / m;

        total = 0.0;
        for(x = 0; x < m; x++) {
            total += pow(atual.relevancias[x] - atual.med, 2);
        }
        atual.dp = sqrt(total / m);

        int c = -1;

        if(atual.med < 60) {
            if(atual.max < 80) {
                c = 0;
            } else {
                if(atual.min <= 20) {
                    c = 1;
                } else {
                    c = 2;
                }
            }
        } else {
            if(atual.dp <= 15) {
                c = 3;
            } else {
                c = 4;
            }
        }

        itens[i] = atual;

        if(c >= 0) {
            classificacoes[c].itens[classificacoes[c].total] = &(itens[i]);
            classificacoes[c].total++;
        }
    }

    for(i = 0; i < n; i++) {
        item atual = itens[i];
        printf("%s %.2lf %.2lf %.2lf %.2lf\n", atual.topico, atual.max, atual.min, atual.med, atual.dp);
    }

    printf("\nRESULTADO:\n");

    for(i = 4; i >= 0; i--) {
        classificacao cAtual = classificacoes[i];
        if(i == 0) printf("Irrelevante");
        else if(i == 1) printf("Local");
        else if(i == 2) printf("Normal");
        else if(i == 3) printf("Surpreendente");
        else if(i == 4) printf("Bot");

        printf(" (%d):", cAtual.total);
        for(x = 0; x < cAtual.total; x++) {
            printf(" %s", cAtual.itens[x]->topico);
        }
        printf("\n");
    }

    for(i = 0; i < 5; i++) {
        free(classificacoes[i].itens);
    }
    free(classificacoes);

    for(i = 0; i < n; i++) {
        free(itens[i].topico);
        free(itens[i].relevancias);
    }
    free(itens);
    return 0;
}
