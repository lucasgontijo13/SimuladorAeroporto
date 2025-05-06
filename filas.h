typedef struct {
    int id;
    int gasolina;
    int ciclo;
} tipo_item;

typedef struct tipo_celula *tipo_apontador;

typedef struct tipo_celula {
    tipo_item item;
    tipo_apontador prox;
} tipo_celula;

typedef struct {
    tipo_apontador primeiro, ultimo;
    int tam;
} tipo_fila;

// Função para inicializar a fila
void cria(tipo_fila *fila);

//funcao para verificar se a fila esta fazia
int vazia(tipo_fila fila);

//funcao para enfileirar aviões
void enfileira(tipo_fila *fila, tipo_item x) ;

//funcao para desenfileirar
tipo_item desenfilera(tipo_fila *fila);

//funcao para imprimir um fila
void imprime(tipo_fila fila);

//funcao para facilitar a impressao de todas as filas de decolagem e aterrissagem
void imprimir_todas(tipo_fila fA1,tipo_fila fA2,tipo_fila fA3,tipo_fila fA4,tipo_fila fD1,tipo_fila fD2,tipo_fila fD3);