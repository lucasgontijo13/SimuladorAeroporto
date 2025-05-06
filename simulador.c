#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filas.h"
#include "F_aeroporto.h"



int main() {
    tipo_fila fila1_ate, fila2_ate, fila3_ate, fila4_ate;
    tipo_fila fila1_dec, fila2_dec, fila3_dec;
    int tempo=0,qtd_deco=0,qtd_ate=0;
    int caidos=0,pousados_um_combus=0;
    float tempo_medio_deco=0,tempo_medio_ate=0;
    //controle 0 aterrissa, 1 decola
    int controle = 0;
    srand(time(NULL));

    // Inicializa as filas
    cria(&fila1_ate);
    cria(&fila2_ate);
    cria(&fila3_ate);
    cria(&fila4_ate);
    cria(&fila1_dec);
    cria(&fila2_dec);
    cria(&fila3_dec);

    printf("Digite a quantidade de tempo que deseja:");
    scanf("%d",&tempo);

    for(int i=0;i<tempo;i++){
        printf("\n----------Gerando Aviões----------\n");
        gera_decolagem(&fila1_dec,&fila2_dec,&fila3_dec,i);
        gera_aterrissagem(&fila1_ate,&fila2_ate,&fila3_ate,&fila4_ate,i);
        imprimir_todas(fila1_ate,fila2_ate,fila3_ate,fila4_ate,fila1_dec,fila2_dec,fila3_dec);
        gerenciar_avioes(&fila1_ate,&fila2_ate,&fila3_ate,&fila4_ate,&fila1_dec,&fila2_dec,&fila3_dec,&caidos,&pousados_um_combus,&tempo_medio_deco,&tempo_medio_ate,&controle,i,&qtd_deco,&qtd_ate);
        decrementa_gasolina(&fila1_ate,&fila2_ate,&fila3_ate,&fila4_ate);
    }

    printf("\nCaiu %d aviões.\n",caidos);
    printf("Aterrisaram %d aviões com 1 de combustivel.\n",pousados_um_combus);
    if(qtd_deco > 0 ){
        tempo_medio_deco = (tempo_medio_deco/qtd_deco);
        printf("Decoloram %d aviões e o tempo médio de decolagem foi: %.2f.\n",qtd_deco,tempo_medio_deco);
    }else{
        printf("Nenhuma avião decolou.");
    }
    if(qtd_ate > 0 ){
        tempo_medio_ate = (tempo_medio_ate/qtd_ate);
        printf("Aterrissaram %d aviões e o tempo médio de aterrissagem foi: %.2f.\n",qtd_ate,tempo_medio_ate);
    }else{
        printf("Nenhuma avião aterrissou.");
    }
    
    
    //comando para quando for executar o simulador.exe pelo explorer ele nao fechar apos concluir
    system("pause"); 
    return 0;
}