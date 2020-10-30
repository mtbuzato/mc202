#include <string.h>

typedef struct ListaAtendimentosNo {
    int profissional;
    struct ListaAtendimentosNo * prox;
    struct ListaAtendimentosNo * ante;
} ListaAtendimentosNo;

typedef struct ListaAtendimentos {
    ListaAtendimentosNo * comeco;
    ListaAtendimentosNo * fim;
} ListaAtendimentos;

typedef struct PessoasNo {
    char nome[50];
    ListaAtendimentos * atendimentos;
    short preferencial;
    short naFila;
    struct PessoasNo * prox;
    struct PessoasNo * ante;
} PessoasNo;

typedef struct Pessoas {
    PessoasNo * comeco;
    PessoasNo * fim;
} Pessoas;

Pessoas pessoas_criar();
Pessoas pessoas_adicionar(Pessoas lista, char nome[], short preferencial);
Pessoas pessoas_remover(Pessoas lista);
void pessoas_destruir(Pessoas lista);

ListaAtendimentos * atendimentos_criar();
void atendimentos_adicionar(ListaAtendimentos *lista, int profissional);
void atendimentos_remover(ListaAtendimentos *lista);
void atendimentos_destruir(ListaAtendimentos *lista);