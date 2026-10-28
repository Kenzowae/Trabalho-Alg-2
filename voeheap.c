#include "voeheap.h"

Heap* InicHeap(int capacidade) {
    Heap *h = (Heap*) malloc(sizeof(Heap));
    if (!h)
        return NULL;
    h->vetor = (Passageiro*) malloc(sizeof(Passageiro));
    if (!(h->vetor))
        return NULL;

    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

int InsereHeap(Heap* h, Passageiro p, Metricas* m) {
}

Passageiro RemoveHeap(Heap* h, Metricas* m) {
}

void Heapfy(Passageiro* vetor,int tamanho, int indice, Metricas* m) {
    int maior = indice;
    int esq = 2 * indice + 1;
    int dir = 2 * indice + 2;

    if(esq < tamanho){
        if(m) m->comparacoes++;

        if(vetor[esq].prioridade > vetor[maior].prioridade)
            maior = esq;
    }
    if(dir < tamanho){
        if(m) m->comparacoes++;

        if(vetor[dir].prioridade > vetor[maior].prioridade)
            maior = dir;
    }

    if(maior != indice){
        TrocaPassageiro(&vetor[indice], &vetor[maior], m);
        Heapfy(vetor, tamanho, maior, m);
    }
}

int ChecaHeap(Heap* h) {
    if (!h || !h->vetor)
        return 0;
    
    if(h->tamanho <= 1)
        return 1;
    
    for(int i = 0;i <= h->tamanho/2; i++){
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
    
        if(esq < h->tamanho && h->vetor[i].prioridade < h->vetor[esq].prioridade)
            return 0;
        
        if(dir < h->tamanho && h->vetor[i].prioridade < h->vetor[dir].prioridade)
            return 0;
    }
    return 1;
}

void ImprimeHeap(Heap* h) {    
    printf("\n--- Fila de Embarque ---\n");

    for(int i = 0; i < h->tamanho; i++)
        printf("Passageiro %s | Prioridade: %d\n", h->vetor[i].nome, h->vetor[i].prioridade );
}

void ConstruirHeap(Heap* h) {
    if (!h || !h->vetor || h->tamanho <= 1)
        return;
    
    for(int i = (h->tamanho/2); i >= 0; i--)
        Heapfy(h->vetor, h->tamanho, i, NULL);
}

void HeapSort(Passageiro* vetor, int n, Metricas* m) {
    int i;
    for(i = n / 2 - 1; i>= 0; i--)
        Heapfy(vetor, n, i, m);

    for (i = n - 1; i > 0; i--){
        TrocaPassageiro(&vetor[0], &vetor[i], m);
        Heapfy(vetor, i, 0, m);
    }
}

int MedianaDeTres(Passageiro* vetor, int inicio, int fim, Metricas* m) {
    int meio = (inicio + fim)/ 2;

    if (m) m->comparacoes++;
    if (vetor[inicio].prioridade > vetor[meio].prioridade)
        TrocaPassageiro(&vetor[inicio], &vetor[meio], m);
    
    if (vetor[inicio].prioridade > vetor[fim].prioridade)
        TrocaPassageiro(&vetor[inicio], &vetor[fim], m);
    
    if (vetor[meio].prioridade > vetor[fim].prioridade)
        TrocaPassageiro(&vetor[meio], &vetor[fim], m);
    
    TrocaPassageiro(&vetor[meio], &vetor[fim], m);

    return fim;
}

int Particiona(Passageiro* vetor, int inicio, int fim, Metricas* m) {
    int indice_pivo = MedianaDeTres(vetor, inicio, fim, m);
    Passageiro pivo = vetor[indice_pivo];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (m) m->comparacoes++;
        if (vetor[j].prioridade <= pivo.prioridade) {
            i++;
            TrocaPassageiro(&vetor[i], &vetor[j], m);
        }
    }
    TrocaPassageiro(&vetor[i + 1], &vetor[fim], m);
    return i + 1;
}

void QuickSort(Passageiro* vetor, int inicio, int fim, Metricas* m) {
    if (inicio < fim){
        int posicao_pivo = Particiona(vetor, inicio, fim, m);
        QuickSort(vetor, inicio, posicao_pivo - 1, m);
        QuickSort(vetor, posicao_pivo + 1, fim, m);
    }
}

void InsertSort(Passageiro* vetor, int n, Metricas* m) {
    int i,j;

    for(i = 2; i <= n; i++){
        Passageiro aux = vetor[i];
        j = i - 1;
        vetor[0] = aux;

        if(m) m->comparacoes++;
        while(aux.prioridade <= vetor[j].prioridade){
            vetor[j + 1] = vetor[j];
            j--;
            if (m){
                m->trocas++;
                m->comparacoes++;
            }
        }
        vetor[j + 1] = aux;
        if(m) m->trocas++;
    }
}

void TrocaPassageiro(Passageiro* a, Passageiro* b, Metricas* m) { 
    Passageiro passageiro_temp = *a;
    *a = *b;
    *b = passageiro_temp;
    if (m)
        m->trocas++;
}

void GeraVetorAleatorio(Passageiro* vetor, int tamanho) {
}

void ComparaAlgoritmos() {
}

void Menu() {
}