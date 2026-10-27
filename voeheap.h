#ifndef VOEHEAP_H
#define VOEHEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definindo o tamanho máximo do nome do passageiro//
#define MAX_NOME 50

// Estrutura para armazenar os dados de cada passageiro //
typedef struct {
    char nome[MAX_NOME];
    int prioridade;
} Passageiro;

// Definindo a estrutura do Heap e das métricas de comparação e troca //
typedef struct {
    Passageiro *vetor; 
    int tamanho;       
    int capacidade;    
} Heap;

// Uma estrutura para armazenar métricas de comparação e troca //
typedef struct {
    long comparacoes;
    long trocas;
} Metricas;


// Função que inicializa o Heap com uma capacidade específica //
Heap* IniciaHeap(int capacidade);

// Função que insere um passageiro no Heap //
int InsereHeap(Heap* h, Passageiro p);

// Função que remove o passageiro com maior prioridade do Heap //
Passageiro RemoveHeap(Heap* h);

// Heapfy adaptado para receber o vetor diretamente, útil para o HeapSort
void Heapfy(Passageiro* vetor, int tamanho, int indice, Metricas* m);

// Função que verifica se o Heap é válido //
int ChecaHeap(Heap* h);

// Função que imprime o Heap //
void ImprimeHeap(Heap* h);

// Função que utiliza o Heapsort para ordenar um vetor de passageiros //
void HeapSort(Passageiro* vetor, int n, Metricas* m);

// Função do QuickSort //
void QuickSort(Passageiro* vetor, int inicio, int fim);

// Mediana de três para o QuickSort //
int MedianaDeTres(Passageiro* vetor, int inicio, int fim);

// Função de partição para o QuickSort //
int Particiona(Passageiro* vetor, int inicio, int fim);

// Função de ordenação pelo Insertion Sort //
void InsertSort(Passageiro* vetor, int n);

// Função auxiliar que troca dois passageiros e incrementa a métrica de trocas //
void TrocaPassageiro(Passageiro* a, Passageiro* b, Metricas* m);

// Função que exibe o menu de opções //
void Menu();

// Função que gera um vetor de passageiros com dados aleatórios //
void GeraVetorAleatorio(Passageiro* vetor, int tamanho);

// Função que compara o desempenho dos algoritmos de ordenação //
void CompararAlgoritmos();

#endif // VOEHEAP_H
