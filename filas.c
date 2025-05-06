#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
#include "F_aeroporto.h"

// Função para inicializar a fila
void cria(tipo_fila *fila) {
    fila->primeiro = (tipo_apontador) malloc(sizeof(tipo_celula));
    if (fila->primeiro == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    fila->ultimo = fila->primeiro;
    fila->primeiro->prox = NULL;
    fila->tam = 0; 
}


//funcao para verificar se a fila esta fazia
int vazia(tipo_fila fila) {
    return (fila.primeiro == fila.ultimo); 
}

//funcao para enfileirar aviões
void enfileira(tipo_fila *fila, tipo_item x) {
    fila->ultimo->prox = (tipo_apontador) malloc(sizeof(tipo_celula));
    if (fila->ultimo->prox == NULL) {
        fprintf(stderr, "Erro de alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    fila->ultimo = fila->ultimo->prox;
    fila->ultimo->item = x;
    fila->ultimo->prox = NULL;
    fila->tam++; 
}

//funcao para desenfileirar aviões
tipo_item desenfilera(tipo_fila *fila) {
    tipo_apontador aux;
    tipo_item aviao;

    aviao.gasolina = -1;
    aviao.id = -1;

    if (vazia(*fila)) {
        printf("\nA fila está vazia\n");
        return aviao;
    }else{
        aux = fila->primeiro->prox;
        fila->primeiro->prox = aux->prox;

        if (fila->primeiro->prox == NULL) {
            fila->ultimo = fila->primeiro; 
        }
        aviao = aux->item;
        free(aux);
        fila->tam--; 
        return aviao;
    }
    
}

//funcao para imprimir um fila
void imprime(tipo_fila fila) {
    if (fila.tam != 0) {
        tipo_apontador aux;
        aux = fila.primeiro->prox;
        while (aux != NULL) {
            printf("ID: %d, Gasolina: %d\n", aux->item.id, aux->item.gasolina);
            aux = aux->prox;
        }
    } else {
        printf("Fila vazia\n");
    }
}

//funcao para facilitar a impressao de todas as filas de decolagem e aterrissagem
void imprimir_todas(tipo_fila fA1,tipo_fila fA2,tipo_fila fA3,tipo_fila fA4,tipo_fila fD1,tipo_fila fD2,tipo_fila fD3){
    printf("\n----------Aviões de Decolagem----------\n");
    printf("Fila de Decolagem 1:\n");
    imprime(fD1);
    printf("\nFila de Decolagem 2:\n");
    imprime(fD2);
    printf("\nFila de Decolagem 3:\n");
    imprime(fD3);
    printf("\n----------Aviões de Aterrissagem----------\n");
    printf("Fila de Aterrissagem 1:\n");
    imprime(fA1);
    printf("\nFila de Aterrissagem 2:\n");
    imprime(fA2);
    printf("\nFila de Aterrissagem 3:\n");
    imprime(fA3);
    printf("\nFila de Aterrissagem 4:\n");
    imprime(fA4);
}
//Fim das funções de fila
