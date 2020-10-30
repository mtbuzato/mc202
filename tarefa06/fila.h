#include "pessoa.h"

typedef struct FilaNo {
    PessoasNo * pessoa;
    struct FilaNo *prox;
    struct FilaNo *ante;
} FilaNo;

typedef struct Fila {
    FilaNo * comeco;
    FilaNo * fim;
} Fila;

Fila fila_adicionar_comeco(Fila fila, PessoasNo *pessoa);
Fila fila_remover_comeco(Fila fila);

Fila fila_adicionar_fim(Fila fila, PessoasNo *pessoa);
Fila fila_remover_fim(Fila fila);

Fila fila_criar();
void fila_destruir(Fila fila);