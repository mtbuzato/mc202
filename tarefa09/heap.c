#ifndef _HEAP_H
#define _HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./heap.h"

// Utilidades estáticas

#define PAI(i)  ((i-1)/2)
#define ESQ(i)  ((2*i)+1)
#define DIR(i)  ((2*i)+2)

/**
 * @brief Cria um novo heap
 * 
 * @param tam Tamanho máximo do heap
 * @return Heap* Ponteiro para a raiz do novo heap
 */
Heap* heap_criar(int tam) {
  Heap* heap = malloc(sizeof(Heap));
  if(heap == NULL) {
    printf("OOM\n");
    exit(0);
  }

  heap->v = malloc(tam * sizeof(Viagem));
  if(heap->v == NULL) {
    printf("OOM\n");
    exit(0);
  }

  heap->n = 0;

  return heap;
}

/**
 * @brief Destrói o heap e libera memória
 * 
 * @param heap Ponteiro para raiz do heap
 * @param tam Tamanho do heap
 */
void heap_destruir(Heap* heap, int tam) {
  free(heap->v);
  free(heap);
}

/**
 * @brief Insere um novo item no heap garantindo a organização por avaliação
 * 
 * @param heap Ponteiro para raiz do heap
 * @param viagem Item para inserir
 */
void heap_inserir(Heap* heap, Viagem viagem) {
  int novo = heap->n;
  heap->v[novo] = viagem;
  heap->n++;
  heap_subir(heap, novo); // Inserimos em baixo e subimos se necessário
}

/**
 * @brief Remove o item que se encontra no endereço x do heap, mantendo a organização por avaliação
 * 
 * @param heap Ponteiro para raiz do heap
 * @param x Endereço do item para remover
 */
void heap_remover(Heap* heap, int x) {
  if(heap->n == 0 || x > heap->n) return;
  if(heap->n == 1) {
    heap->n--;
    return;
  }

  heap_trocar(heap, x, heap->n - 1);    // Trocamos pelo último endereço (menor) e descemos ele, caso necessário
  heap->n--;
  heap_descer(heap, x);
}

/**
 * @brief Sobe, caso necessário, um item de endereço no heap, garantindo a organização por avaliação
 * 
 * @param heap Ponteiro para raiz do heap
 * @param x Endereço do heap para tentar subir
 */
void heap_subir(Heap* heap, int x) {
  if(PAI(x) >= 0 && heap_maior(heap, x, PAI(x))) {  // Verifica se tem pai e se é preciso subir
    heap_trocar(heap, x, PAI(x));
    heap_subir(heap, PAI(x));
  }
}

/**
 * @brief Desce, caso necessário, um item de endereço no heap, garantindo a organização por avaliação
 * 
 * @param heap Ponteiro para raiz do heap
 * @param x Endereço do heap para tentar descer
 */
void heap_descer(Heap* heap, int x) {
  int maior;
  if(ESQ(x) < heap->n) {  // Verifica se tem filho esquerdo
    maior = ESQ(x);
    if(DIR(x) < heap->n && heap_maior(heap, DIR(x), ESQ(x))) maior = DIR(x);  // Verifica se tem direito, e se é maior que esquerdo

    if(heap_maior(heap, maior, x)) {  // Troca com o maior, se for maior que ele mesmo
      heap_trocar(heap, x, maior);
      heap_descer(heap, maior);
    }
  }
}

/**
 * @brief Troca itens de lugar no heap
 * 
 * @param heap Ponteiro para raiz do heap
 * @param a Item A
 * @param b Item B
 */
void heap_trocar(Heap* heap, int a, int b) {
  Viagem temp = heap->v[a]; // Não foi necessário verificar existência pois todos locais que usam essa função já fazem isso (eficiência)
  heap->v[a] = heap->v[b];
  heap->v[b] = temp;
}

/**
 * @brief Retorna 1 se a avaliação de A for maior que a avaliação de B
 * 
 * @param heap Ponteiro para raiz do heap
 * @param a Endereço de A
 * @param b Endereço de B
 * @return int 1 se a > b, 0 caso contrário
 */
int heap_maior(Heap* heap, int a, int b) {
  double avaA = heap->v[a].avaliacao; // Novamente não é necessário verificar existência
  double avaB = heap->v[b].avaliacao;

  return avaA > avaB;
}

/**
 * @brief Pega a próxima viagem a ser feita(maior avaliação) e reorganiza o heap por avaliação
 * 
 * @param heap Ponteiro para raiz do heap
 * @return Viagem Próxima viagem
 */
Viagem heap_proximo(Heap* heap) {
  if(heap->n == 0) {  // Se o heap estiver vazio, retornamos uma viagem com avaliação -1 (considerada NULL)
    Viagem v;
    v.avaliacao = -1;
    return v;
  } else if(heap->n == 1) {
    heap->n--;      // Se o heap tiver 1 viagem só, não nos preocupamos em trocar nada de lugar
    return heap->v[0];
  }

  Viagem heap_maior = heap->v[0];
  heap_trocar(heap, 0, heap->n - 1);
  heap->n--;
  heap_descer(heap, 0);
  return heap_maior;
}

/**
 * @brief Retorna o endereço da viagem cujo cliente tenha o nome, ou -1 se não houver
 * 
 * @param heap Ponteiro para raiz do heap
 * @param nome Nome pra buscar
 * @return int Endereço encontrado
 */
int heap_encontrar(Heap* heap, char nome[]) {
  for(int i = 0; i < heap->n; i++) {  // Itera todos os itens do heap em busca do nome
    if(strcmp(heap->v[i].nome, nome) == 0) {
      return i;
    }
  }

  return -1;
}

#endif