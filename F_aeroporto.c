#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
#include "F_aeroporto.h"

//função para gerar o ID unico dos aviões
int gerar_id_unico(int par) {
    static int id_atual_par = 2;
    static int id_atual_impar = 1; 

    int id_unico;

    if (par == 1) { 
        id_unico = id_atual_par;
        id_atual_par += 2; 
    } else { 
        id_unico = id_atual_impar;
        id_atual_impar += 2; 
    }

    return id_unico;
}

//Função para ver qual fila é menor nas aterrissagem para colocar o aviao nela
int fila_menor_aterrissagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,tipo_fila *fila4){
    tipo_fila *aux;
    aux = fila1;
    int fila_menor=1;

    if (aux->tam > fila2->tam) {
        aux = fila2;
        fila_menor = 2;
    }
    if (aux->tam > fila3->tam) {
        aux = fila3;
        fila_menor = 3;
    }
    if (aux->tam > fila4->tam) {
        aux = fila4;
        fila_menor = 4;
    }
    return fila_menor;
}

//Função para ver qual fila é menor nas decolagem para colocar o aviao nela
int fila_menor_decolagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3){
    tipo_fila *aux;
    aux = fila3;
    int fila_menor=3;

    if (aux->tam > fila2->tam) {
        aux = fila2;
        fila_menor = 2;
    }
    if (aux->tam > fila1->tam) {
        aux = fila1;
        fila_menor = 1;
    }

    return fila_menor;
}

//Função para gerar aviões nas filas de aterrissagem
void gera_aterrissagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,tipo_fila *fila4, int loop){
    int qtd_aviao;
    int menor=0;
    int par = 0;
    tipo_item aviao;


    qtd_aviao = rand() % 4; //gera entre 0 e 3
    printf("\nQuantidade aviões gerados na fila de aterrissagem = %d\n",qtd_aviao);
    for(int i=0;i<qtd_aviao;i++){
        aviao.ciclo = loop;
        printf("\n\nLOOP %d\n\n",loop);
        aviao.gasolina = (rand() % 20) + 1; // ; gera entre 1 e 20
        aviao.id = gerar_id_unico(par);
        menor=fila_menor_aterrissagem(fila1,fila2,fila3,fila4);
        if(menor==1){
            enfileira(fila1,aviao);
        }else if (menor==2){
            enfileira(fila2,aviao);
        }else if (menor==3){
            enfileira(fila3,aviao);
        }else if (menor==4){
            enfileira(fila4,aviao);
        }

    }
     
}

//Função para gerar aviões nas filas de decolagem
void gera_decolagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3, int loop){
    int qtd_aviao;
    int menor=0;
    int par = 1;
    tipo_item aviao;
    qtd_aviao = rand() % 4; //gera entre 0 e 3
    printf("\nQuantidade aviao de aviões gerados na fila de decolagem = %d\n",qtd_aviao);
    for(int i=0;i<qtd_aviao;i++){
        aviao.ciclo = loop;
        aviao.gasolina = 20;
        aviao.id = gerar_id_unico(par);
        menor=fila_menor_decolagem(fila1,fila2,fila3);
        if(menor==1){
            enfileira(fila1,aviao);
        }else if (menor==2){
            enfileira(fila2,aviao);
        }else if (menor==3){
            enfileira(fila3,aviao);
        }
    }
}

//Função para retirar os avioes que chegam na primeira posição da fila com menos de 1 de gasolina
void retira_caidos(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,tipo_fila *fila4,int *caidos){
    tipo_item aviao;
    if(!vazia(*fila1) && fila1->primeiro->prox->item.gasolina < 1 ){
        aviao=desenfilera(fila1);
        printf("\nAvião da fila 1 com id %d caiu.\n",aviao.id);
        (*caidos)++;
    }
    if(!vazia(*fila2) && fila2->primeiro->prox->item.gasolina < 1 ){
        aviao=desenfilera(fila2);
        printf("\nAvião da fila 1 com id %d caiu.\n",aviao.id);
        (*caidos)++;
    }
    if(!vazia(*fila3) && fila3->primeiro->prox->item.gasolina < 1 ){
        aviao=desenfilera(fila3);
        printf("\nAvião da fila 1 com id %d caiu.\n",aviao.id);
        (*caidos)++;
    }
    if(!vazia(*fila4) && fila4->primeiro->prox->item.gasolina < 1 ){
        aviao=desenfilera(fila4);
        printf("\nAvião da fila 1 com id %d caiu.\n",aviao.id);
        (*caidos)++;
    }
}

//Função para gerenciar quais aviões irão para cada pista
void gerenciar_avioes(tipo_fila *fA1,tipo_fila *fA2,tipo_fila *fA3,tipo_fila *fA4,tipo_fila *fD1,tipo_fila *fD2,tipo_fila *fD3,int *caidos,int *pousados_um_combus,float *tempo_medio_deco, float *tempo_medio_ate, int *controle,int loop,int *qtd_deco, int *qtd_ate){
    int pista[3]={0,0,0};
    tipo_item aviao;
    int flagfA1=0,flagfA2=0,flagfA3=0,flagfA4=0;

    printf("\n");
    //FUnção para retirar os avioes que tem menos de 1 gasolina
    retira_caidos(fA1,fA2,fA3,fA4,caidos);


    //a media estava fazendo assim pois foi assim que entendi mas nao me pareceu mt certo entao mudei
   // *tempo_medio_ate += fA1->tam + fA2->tam + fA3->tam + fA4->tam;
    //*tempo_medio_deco += fD1->tam + fD2->tam + fD3->tam;

     //VERIFICANDO SE AVIAO ESTA QUASE CAINDO PARA IR PARA PISTA DE EMERGENCIA
    if (!vazia(*fA1) && fA1->primeiro->prox->item.gasolina == 1) {
        aviao=desenfilera(fA1);
        printf("Avião da fila 1 com id %d com %d gasolina aterrissou na pista de emergencia.\n",aviao.id,aviao.gasolina);
        (*pousados_um_combus)++;
        pista[2]=1;
        flagfA1=1;
        (*tempo_medio_ate) += (loop - aviao.ciclo);
        (*qtd_ate)++;

    }
    if (!vazia(*fA2) && fA2->primeiro->prox->item.gasolina == 1 && pista[2] == 0) {
        aviao=desenfilera(fA2);
        printf("Avião da fila 2 com id %d com %d gasolina aterrissou na pista de emergencia.\n",aviao.id,aviao.gasolina);
        (*pousados_um_combus)++;
        pista[2]=1;
        flagfA2=1;
       (*tempo_medio_ate) += (loop - aviao.ciclo);
       (*qtd_ate)++;
    }
    if (!vazia(*fA3) && fA3->primeiro->prox->item.gasolina == 1 && pista[2] == 0) {
        aviao=desenfilera(fA3);
        printf("Avião da fila 3 com id %d com %d gasolina aterrissou na pista de emergencia.\n",aviao.id,aviao.gasolina);
       (*pousados_um_combus)++;
        pista[2]=1;
        flagfA3=1;
        (*tempo_medio_ate) += (loop - aviao.ciclo);
        (*qtd_ate)++;
    }
    if (!vazia(*fA4) && fA4->primeiro->prox->item.gasolina == 1 && pista[2] == 0) {
        aviao=desenfilera(fA4);
        printf("Avião da fila 4 com id %d com %d gasolina aterrissou na pista de emergencia.\n",aviao.id,aviao.gasolina);
        (*pousados_um_combus)++;
        pista[2]=1;
        flagfA4=1;
        (*tempo_medio_ate) += (loop - aviao.ciclo);
        (*qtd_ate)++;
    }
    // FIM VERIFICANDO SE AVIAO ESTA QUASE CAINDO




    //se controle = 0 quer dizer que é o controle de aterrissagem
    if((*controle) == 0){
        printf("Vez de aterrissar.\n");
        //Verificando se tem aviao na fila de aterrisagem  1 e 2, e qual vai descer
        if(!vazia(*fA1) && !vazia(*fA2)){
            if((fA1->primeiro->prox->item.gasolina < fA2->primeiro->prox->item.gasolina && flagfA1 == 0) || (flagfA2 != 0 && flagfA1 == 0)){
                aviao=desenfilera(fA1);
                printf("Avião da fila 1 com id %d com %d gasolina aterrissou na pista 1.\n",aviao.id,aviao.gasolina);
                pista[0]=1;
                (*tempo_medio_ate) += (loop - aviao.ciclo);
                (*qtd_ate)++;
                if(aviao.gasolina == 1){
                    (*pousados_um_combus)++;
                }
            }else{
                aviao=desenfilera(fA2);
                printf("Avião da fila 2 com id %d com %d gasolina aterrissou na pista 1.\n",aviao.id,aviao.gasolina);
                pista[0]=1;
                (*tempo_medio_ate) += (loop - aviao.ciclo);
                (*qtd_ate)++;
                if(aviao.gasolina == 1){
                    (*pousados_um_combus)++;
                }
            }
        }else if(vazia(*fA1) && !vazia(*fA2) && flagfA2 == 0){
            aviao=desenfilera(fA2);
            printf("Avião da fila 2 com id %d com %d gasolina aterrissou na pista 1.\n",aviao.id,aviao.gasolina);
            pista[0]=1;
            (*tempo_medio_ate) += (loop - aviao.ciclo);
            (*qtd_ate)++;
            if(aviao.gasolina == 1){
                (*pousados_um_combus)++;
            }
        }else if(!vazia(*fA1) && vazia(*fA2) && flagfA1 == 0){
            aviao=desenfilera(fA1);
            printf("Avião da fila 1 com id %d com %d gasolina aterrissou na pista 1.\n",aviao.id,aviao.gasolina);
            pista[0]=1;
            (*tempo_medio_ate) += (loop - aviao.ciclo);
            (*qtd_ate)++;
            if(aviao.gasolina == 1){
                (*pousados_um_combus)++;
            }
        }
        

        //Verificando se tem aviao na fila de aterrisagem  3 e 4, e qual vai descer
        if(!vazia(*fA3) && !vazia(*fA4)){
            if((fA3->primeiro->prox->item.gasolina < fA4->primeiro->prox->item.gasolina && flagfA3 == 0) || (flagfA4 != 0 && flagfA3 == 0)){
                aviao=desenfilera(fA3);
                printf("Avião da fila 3 com id %d com %d gasolina aterrissou na pista 2.\n",aviao.id,aviao.gasolina);
                pista[1]=1;
                (*tempo_medio_ate) += (loop - aviao.ciclo);
                (*qtd_ate)++;
                if(aviao.gasolina == 1){
                    (*pousados_um_combus)++;
                }
            }else{
                aviao=desenfilera(fA4);
                printf("Avião da fila 4 com id %d com %d gasolina aterrissou na pista 2.\n",aviao.id,aviao.gasolina);
                pista[1]=1;
                (*tempo_medio_ate) += (loop - aviao.ciclo);
                (*qtd_ate)++;
                if(aviao.gasolina == 1){
                    (*pousados_um_combus)++;
                }
            }
        }else if(vazia(*fA3) && !vazia(*fA4) && flagfA4 == 0){
            aviao=desenfilera(fA4);
            printf("Avião da fila 4 com id  %d com %d gasolina aterrissou na pista 2.\n",aviao.id,aviao.gasolina);
            pista[1]=1;
            (*tempo_medio_ate) += (loop - aviao.ciclo);
            (*qtd_ate)++;
            if(aviao.gasolina == 1){
                (*pousados_um_combus)++;
            }
        }else if(!vazia(*fA3) && vazia(*fA4) && flagfA3 == 0){
            aviao=desenfilera(fA3);
            printf("Avião da fila 3 com id %d com %d gasolina aterrissou na pista 2.\n",aviao.id,aviao.gasolina);
            pista[1]=1;
            (*tempo_medio_ate) += (loop - aviao.ciclo);
            (*qtd_ate)++;
            if(aviao.gasolina == 1){
                (*pousados_um_combus)++;
            }
        }
    
    }
    
   
    
    
    //se controle = 1 quer dizer que é o controle de decolagem
    if (*controle == 1){
        printf("Vez de decolar.\n");
        if(!vazia(*fD1) && pista[0]==0){
            aviao=desenfilera(fD1);
            printf("Avião da fila 1 com id %d com %d gasolina decolou na pista 1.\n",aviao.id,aviao.gasolina); 
            pista[0]=1;
            (*tempo_medio_deco) += (loop - aviao.ciclo);
            (*qtd_deco)++;
        }

        //Verificando a pista 2 para decolar
        if(!vazia(*fD2) && pista[1]==0){
            aviao=desenfilera(fD2);           
            printf("Avião da fila 2 com id %d com %d gasolina decolou na pista 2.\n",aviao.id,aviao.gasolina);
            pista[1]=1;
            (*tempo_medio_deco) += (loop - aviao.ciclo);
            (*qtd_deco)++;
        }
        (*controle)--;
    }else{
        (*controle)++;
    }
    
    


    //Decolando na pista esclusiva de decolagem
    if(pista[2] == 0 && !vazia(*fD3)){
        aviao=desenfilera(fD3);
        printf("Avião da fila 3 com id %d com %d gasolina decolou na pista 3.\n",aviao.id,aviao.gasolina); 
        pista[2]=1;
        (*tempo_medio_deco) += (loop - aviao.ciclo);
        (*qtd_deco)++;
       
    }
     
}

//Função para tirar um de gasolina de cada aviao
void decrementa_gasolina(tipo_fila *fA1,tipo_fila *fA2,tipo_fila *fA3,tipo_fila *fA4){
   tipo_apontador atual;

    // Decrementa gasolina na fila fA1
    atual = fA1->primeiro;
    while (atual != NULL) {
        atual->item.gasolina--;
        atual = atual->prox;
    }

    // Decrementa gasolina na fila fA2
    atual = fA2->primeiro;
    while (atual != NULL) {
        atual->item.gasolina--;
        atual = atual->prox;
    }
    // Decrementa gasolina na fila fA3
    atual = fA3->primeiro;
    while (atual != NULL) {
        atual->item.gasolina--;
        atual = atual->prox;
    }

    // Decrementa gasolina na fila fA4
    atual = fA4->primeiro;
    while (atual != NULL) {
        atual->item.gasolina--;
        atual = atual->prox;
    }
}