#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int distancia(int deX, int deY, int paraX, int paraY) {
  return abs(deX - paraX) + abs(deY - paraY);
}

int main() {
  char cmd;
  int x = 0, y = 0, kilometragem = 0;
  double despesas = 57.0, rendimentos = 0.0;
  Heap* heap = heap_criar(15);
  Viagem atual;
  atual.avaliacao = -1;

  while(scanf(" %c", &cmd) > 0) {
    switch (cmd) {
      case 'A': ;
        Viagem v;

        scanf("%s %lf %d %d %d %d ", v.nome, &v.avaliacao, &v.deX, &v.deY, &v.paraX, &v.paraY);

        if(atual.avaliacao == -1) {
          atual = v;
        } else {
          heap_inserir(heap, v);
        }

        printf("Cliente %s foi adicionado(a)\n", v.nome);
        break;

      case 'F': ;
        int corrida = distancia(atual.deX, atual.deY, atual.paraX, atual.paraY);
        int total = distancia(x, y, atual.deX, atual.deY) + corrida;

        kilometragem += total;
        rendimentos += corrida * 1.40;
        despesas += total * 0.4104;
        x = atual.paraX;
        y = atual.paraY;

        printf("A corrida de %s foi finalizada\n", atual.nome);

        atual = heap_proximo(heap);
        break;
      
      case 'C': ;
        char nome[15];

        scanf("%s ", nome);

        int x = heap_encontrar(heap, nome);

        if(x < 0) {
          printf("%s não heap_encontrardo.\n", nome);
          exit(0);
        }

        heap_remover(heap, x);
        rendimentos += 7;

        printf("%s cancelou a corrida\n", nome);
        break;
      
      case 'T': ;
          printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
          printf("Km total: %d\n", kilometragem);
          printf("Rendimento bruto: %.2lf\n", rendimentos);
          printf("Despesas: %.2lf\n", despesas);
          printf("Rendimento liquido: %.2lf\n", (rendimentos * 0.75) - despesas);
        break;
      
      default:
        printf("Comando inválido.\n");
        exit(0);
        break;
    }
  }

  heap_destruir(heap, 15);

  return 0;
}