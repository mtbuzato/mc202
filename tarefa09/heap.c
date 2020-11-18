#ifndef _HEAP_H
#define _HEAP_H

#include <stdlib.h>
#include <string.h>
#include "./heap.h"

#define PAI(i)  ((i-1)/2)
#define ESQ(i)  ((2*i)+1)
#define DIR(i)  ((2*i)+2)

Heap* heap_criar(int tam) {
  Heap* heap = malloc(sizeof(Heap));
  heap->v = malloc(tam * sizeof(Viagem));
  heap->n = 0;

  return heap;
}

void heap_destruir(Heap* heap, int tam) {
  free(heap->v);
  free(heap);
}

void heap_inserir(Heap* heap, Viagem viagem) {
  int novo = heap->n;
  heap->v[novo] = viagem;
  heap->n++;
  heap_subir(heap, novo);
}

void heap_remover(Heap* heap, int x) {
  if(heap->n == 0 || x > heap->n) return;
  if(heap->n == 1) {
    heap->n--;
    return;
  }

  heap_trocar(heap, x, heap->n - 1);
  heap->n--;
  heap_descer(heap, x);
}

void heap_subir(Heap* heap, int x) {
  if(PAI(x) >= 0 && heap_maior(heap, x, PAI(x))) {
    heap_trocar(heap, x, PAI(x));
    heap_subir(heap, PAI(x));
  }
}

void heap_descer(Heap* heap, int x) {
  int maior;
  if(ESQ(x) < heap->n) {
    maior = ESQ(x);
    if(DIR(x) < heap->n && heap_maior(heap, DIR(x), ESQ(x))) maior = DIR(x);

    if(heap_maior(heap, maior, x)) {
      heap_trocar(heap, x, maior);
      heap_descer(heap, maior);
    }
  }
}

void heap_trocar(Heap* heap, int a, int b) {
  Viagem temp = heap->v[a];
  heap->v[a] = heap->v[b];
  heap->v[b] = temp;
}

int heap_maior(Heap* heap, int a, int b) {
  double avaA = heap->v[a].avaliacao;
  double avaB = heap->v[b].avaliacao;

  return avaA > avaB;
}

Viagem heap_proximo(Heap* heap) {
  if(heap->n == 0) {
    Viagem v;
    v.avaliacao = -1;
    return v;
  } else if(heap->n == 1) {
    heap->n--;
    return heap->v[0];
  }

  Viagem heap_maior = heap->v[0];
  heap_trocar(heap, 0, heap->n - 1);
  heap->n--;
  heap_descer(heap, 0);
  return heap_maior;
}

int heap_encontrar(Heap* heap, char nome[]) {
  for(int i = 0; i < heap->n; i++) {
    if(strcmp(heap->v[i].nome, nome) == 0) {
      return i;
    }
  }

  return -1;
}

#endif