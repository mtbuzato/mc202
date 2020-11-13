typedef struct No {
    int dado;
    char chave[750];
    struct No* esq, *dir;
} No;

No* criar(int dado, char chave[], No* esq, No* dir);
void destruir(No* raiz);

No* adicionar(No* raiz, int dado, char chave[]);
No* remover(No* raiz, No* x);

No* sucessor(No* raiz, No* x);
No* antecessor(No* raiz, No* x);

No* minimo(No* x);
No* maximo(No* x);