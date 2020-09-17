#include <stdio.h>

int main() {
    int apostadores;
    float premio;

    scanf("%d %f", &apostadores, &premio);

    int primeiraFaixa = 0;
    int segundaFaixa = 0;
    int terceiraFaixa = 0;

    int apostas[1000][15];   // o máximo de apostadores é 1000, cada um com até 15 números
    int status[1000];

    for(int apostador = 0; apostador < apostadores; apostador++) {  // salvar as matrizes de aposta
        int apostaAtual = 0;

        for(int l = 0; l < 6; l++) {
            int apostaLinha[10];

            scanf("%d %d %d %d %d %d %d %d %d %d", &apostaLinha[0], &apostaLinha[1], &apostaLinha[2], &apostaLinha[3], &apostaLinha[4], &apostaLinha[5], &apostaLinha[6], &apostaLinha[7], &apostaLinha[8], &apostaLinha[9]);        // ler a aposta

            for(int i = 0; i < 10; i++) {
                if(apostaLinha[i] == 1) {
                    apostas[apostador][apostaAtual] = i + (10 * l) + 1;      // calcular o número equivalente da aposta, pois a matriz não importa, apenas os 6 números apostados
                    apostaAtual++;
                }
            }
        }
    }

    int sorteio[6]; // salvar o sorteio

    scanf("%d %d %d %d %d %d", &sorteio[0], &sorteio[1], &sorteio[2], &sorteio[3], &sorteio[4], &sorteio[5]);

    for(int apostador = 0; apostador < apostadores; apostador++) {  // ver quantos ganharam
        int acertos = 0;

        for(int x = 0; x < 6; x++) {
            for(int y = 0; y < 15; y++) {
                if(apostas[apostador][y] == sorteio[x]) {
                    acertos++;
                }
            }
        }

        if(acertos == 6) {
            primeiraFaixa++;
            status[apostador] = 1;
        } else if(acertos == 5) {
            segundaFaixa++;
            status[apostador] = 2;
        } else if(acertos == 4) {
            terceiraFaixa++;
            status[apostador] = 3;
        } else {
            status[apostador] = 0;
        }
    }

    double premios[4] = {0.0, (premio * 0.62) / primeiraFaixa, (premio * 0.19) / segundaFaixa, (premio * 0.19) / terceiraFaixa}; // double para acertar a precisão do prêmio

    for(int apostador = 0; apostador < apostadores; apostador++) { // mostrar quanto ganharam
        printf("%.2f\n", premios[status[apostador]]);
    }

    return 0;
}