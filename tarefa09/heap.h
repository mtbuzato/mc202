typedef struct {
  int deX, deY, paraX, paraY;
  char nome[15];
  double avaliacao;
} Viagem;

typedef struct {
  Viagem *v;
  int n;
} Heap;

Heap* heap_criar(int tam);

void heap_destruir(Heap* heap, int tam);

void heap_inserir(Heap* heap, Viagem viagem);

void heap_remover(Heap* heap, int x);

void heap_subir(Heap* heap, int x);

void heap_descer(Heap* heap, int x);

void heap_trocar(Heap* heap, int a, int b);

int heap_maior(Heap* heap, int a, int b);

Viagem heap_proximo(Heap* heap);

int heap_encontrar(Heap* heap, char nome[]);