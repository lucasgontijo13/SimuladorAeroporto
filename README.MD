**Simulador de Aeroporto em C**

**Última Atualização:** Maio 2025

## Descrição

Este projeto implementa um simulador de aeroporto em linguagem C, gerenciando filas de aterrissagem e decolagem de aeronaves. O simulador utiliza TADs de fila para organizar as operações, garantindo prioridades baseadas no nível de combustível e equilibrando cargas entre múltiplas pistas.

## Funcionalidades

* Geração aleatória de aviões para pouso e decolagem.
* Priorização de aviões com menos combustível (incluindo pista de emergência para casos críticos).
* Balanceamento dinâmico das filas de aterrissagem (4 filas) e decolagem (3 filas), usando sempre a fila com menor tamanho.
* Cálculo de tempo médio de espera para pousos e decolagens.
* Contagem de aviões que caem por falta de combustível.
* Saída detalhada de eventos (geração, pouso, decolagem, quedas).

## Pré-requisitos

* Compilador C (GCC, Clang ou equivalente)
* Sistema compatível com POSIX (Linux, macOS) ou MinGW no Windows

## Estrutura do Projeto

```
/ (raiz do projeto)
├── simulador.c     # Função main e loop principal de simulação
├── F_aeroporto.c   # Lógica de gerenciamento de filas e operações de pista
├── filas.c         # Implementação do TAD Fila (lista encadeada)
├── filas.h         # Definições de tipos e protótipos das funções de fila
├── F_aeroporto.h   # Protótipos das funções do simulador de aeroporto
└── README.md       # Documentação do projeto
```

## Compilação

No diretório raiz do projeto, execute:

```bash
gcc -o simulador simulador.c F_aeroporto.c filas.c -std=c99 -Wall
```

## Uso

Após a compilação, inicie a simulação com:

```bash
./simulador
```

O programa pedirá um valor inteiro positivo correspondente ao número de ciclos de tempo a simular. Em cada ciclo:

1. São gerados novos aviões para pouso e decolagem.
2. As filas são exibidas no console.
3. As pistas são gerenciadas (pousos, decolagens, emergências).
4. A quantidade de combustível de cada avião em espera para pouso é decrementada.

Ao término, são exibidos no console:

* Quantidade de aviões que caíram.
* Quantidade de aviões pousados com 1 unidade de combustível.
* Tempo médio de decolagem e aterrissagem.

## Módulos e Principais Funções

### simulador.c

* **main**: Inicializa estruturas, lê o número de ciclos e executa o loop de simulação.

### F\_aeroporto.c / F\_aeroporto.h

* **gerar\_id\_unico(int par)**: Gera IDs alternados (pares para decolagem, ímpares para aterrissagem).
* **fila\_menor\_aterrissagem(...)**: Escolhe a fila de pouso com menor tamanho.
* **fila\_menor\_decolagem(...)**: Escolhe a fila de decolagem com menor tamanho.
* **gera\_aterrissagem(...)**: Insere aviões nas filas de aterrissagem com combustível aleatório.
* **gera\_decolagem(...)**: Insere aviões nas filas de decolagem com combustível fixo.
* **retira\_caidos(...)**: Remove aviões que ficaram sem combustível.
* **gerenciar\_avioes(...)**: Controla pousos e decolagens, alterna pistas e atualiza estatísticas.
* **decrementa\_gasolina(...)**: Decrementa a gasolina de cada avião nas filas de pouso.

### filas.c / filas.h

* **cria(tipo\_fila \*fila)**: Inicializa a fila encadeada.
* **vazia(tipo\_fila fila)**: Verifica se a fila está vazia.
* **enfileira(tipo\_fila \*fila, tipo\_item x)**: Enfileira um avião.
* **desenfilera(tipo\_fila \*fila)**: Desenfileira e retorna o primeiro avião.
* **imprime(tipo\_fila fila)**: Imprime o conteúdo da fila.
* **imprimir\_todas(...)**: Exibe todas as filas de pouso e decolagem.

## Exemplo de Execução

```text
Digite a quantidade de tempo que deseja: 5

----------Gerando Aviões----------
Quantidade aviões gerados na fila de aterrissagem = 1
Quantidade aviões gerados na fila de decolagem = 2
...
Caiu 0 aviões.
Aterrissaram 3 aviões com 1 de combustível.
Decolaram 4 aviões e o tempo médio de decolagem foi: 2.50.
Aterrissaram 4 aviões e o tempo médio de aterrissagem foi: 3.00.
```

## Autor

Lucas Gontijo Rodrigues

---

*Projeto acadêmico em Estruturas de Dados e Programação em C.*
