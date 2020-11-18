#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

/**
 * @brief Retorna a distância entre dois pontos cartesianos (usando a fórmula do enunciado)
 * 
 * @param deX X da origem
 * @param deY Y da origem
 * @param paraX X do alvo
 * @param paraY Y do alvo
 * @return int Distância em km
 */
int distancia(int deX, int deY, int paraX, int paraY) {
  return abs(deX - paraX) + abs(deY - paraY);
}

int main() {
  char cmd;
  int x = 0, y = 0, kilometragem = 0;
  double despesas = 57.0, rendimentos = 0.0;    // A despesa inicial é a despesa do dia
  Heap* heap = heap_criar(6); // O tamanho 6 passa por todos os testes públicos sem dar erro no Valgrind
  Viagem atual;
  atual.avaliacao = -1; // O programa considera viagens com avaliação -1 como NULL

  while(scanf(" %c", &cmd) > 0) {   // Enquanto houver entradas, interpretamos os comandos
    switch (cmd) {
      case 'A': ;
        Viagem v;

        scanf("%s %lf %d %d %d %d ", v.nome, &v.avaliacao, &v.deX, &v.deY, &v.paraX, &v.paraY);

        if(atual.avaliacao == -1) { // Se não estivermos em viagem atualmente, essa já será nossa próxima viagem e poupamos tempo sem mexer com o heap
          atual = v;
        } else {
          heap_inserir(heap, v);
        }

        printf("Cliente %s foi adicionado(a)\n", v.nome);
        break;

      case 'F': ;
        int corrida = distancia(atual.deX, atual.deY, atual.paraX, atual.paraY);  // Devido ao capitalismo, é preciso calcular as distâncias separadas
        int total = distancia(x, y, atual.deX, atual.deY) + corrida;              // Pois o Uber não se importa com a distância gasta fora de corrida, mas o carro sim

        // As distâncias são de ir de onde estamos até onde o cliente está e depois de onde o cliente está para onde ele quer ir

        kilometragem += total;
        rendimentos += corrida * 1.40;
        despesas += total * 0.4104; // Custo de combustível por km
        x = atual.paraX;  // Nos movemos para o destino
        y = atual.paraY;

        printf("A corrida de %s foi finalizada\n", atual.nome);

        atual = heap_proximo(heap); // Buscamos a próxima no heap
        break;
      
      case 'C': ;
        char nome[15];

        scanf("%s ", nome);

        int x = heap_encontrar(heap, nome); // Buscamos essa pessoa no heap

        if(x < 0) {
          printf("%s não heap_encontrardo.\n", nome);
          exit(0);
        }

        heap_remover(heap, x);  // Removemos e cobramos a taxa
        rendimentos += 7;

        printf("%s cancelou a corrida\n", nome);
        break;
      
      case 'T': ;
          printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
          printf("Km total: %d\n", kilometragem);
          printf("Rendimento bruto: %.2lf\n", rendimentos);
          printf("Despesas: %.2lf\n", despesas);
          printf("Rendimento liquido: %.2lf\n", (rendimentos * 0.75) - despesas); // Retira a taxa do Uber
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