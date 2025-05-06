//função para gerar o ID unico dos aviões
int gerar_id_unico(int par);

//Função para ver qual fila é menor nas aterrissagem para colocar o aviao nela
int fila_menor_aterrissagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,tipo_fila *fila4);

//Função para ver qual fila é menor nas decolagem para colocar o aviao nela
int fila_menor_decolagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3);

//Função para gerar aviões nas filas de aterrissagem
void gera_aterrissagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,tipo_fila *fila4, int loop);

//Função para gerar aviões nas filas de decolagem
void gera_decolagem(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,int loop);

//Função para retirar os avioes que chegam na primeira posição da fila com menos de 1 de gasolina
void retira_caidos(tipo_fila *fila1,tipo_fila *fila2,tipo_fila *fila3,tipo_fila *fila4,int *caidos);

//Função para gerenciar quais aviões irão para cada pista
void gerenciar_avioes(tipo_fila *fA1,tipo_fila *fA2,tipo_fila *fA3,tipo_fila *fA4,tipo_fila *fD1,tipo_fila *fD2,tipo_fila *fD3,int *caidos,int *pousados_um_combus,float *tempo_medio_deco, float *tempo_medio_ate, int *controle,int loop, int *qtd_deco,int *qtd_ate);

//Função para tirar um de gasolina de cada aviao
void decrementa_gasolina(tipo_fila *fA1,tipo_fila *fA2,tipo_fila *fA3,tipo_fila *fA4);