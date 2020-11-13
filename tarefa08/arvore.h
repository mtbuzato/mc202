typedef struct No {
    int chave;
    struct No* esq, *dir;
    int altura;
    int ocorrencias;
} No;

int max(int a, int b);

No* criar(int chave);
void destruir(No* raiz);

int altura(No* x);

No* rodarPraDireita(No* x);
No* rodarPraEsquerda(No* x);

int balanco(No* x);

No* adicionar(No* raiz, int chave);

No* encontrar(No* raiz, int chave);