#include "voeheap.h"

void main(){
    int capacidade_inicial = 50;
    Heap *meuHeap = InicHeap(capacidade_inicial);
    if (meuHeap == NULL) {
        printf("Erro fatal: Nao foi possivel alocar o heap.\n");
    }
    Menu(meuHeap);
    free(meuHeap->vetor);
    free(meuHeap);
}


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
    int i = h->tamanho;
    //Verificar se o heap existe // 
    if(h == NULL){ 
    printf("/n O heap não existe!"); 
    return 0; 
    }
    // Verificar o tamanho ̣//
    if(h->tamanho >= h->capacidade){ 
        printf("/n O heap está lotado"); 
        return 0; 
    }
    //Inserir no fim da fila // 
    h->vetor[i] = p; 
    // Atualizar o tamanho // 
    h->tamanho++;

    // bubble up // 
    int pai = (i-1)/2;
    
      while(i > 0){
        if (m) m->comparacoes++;

        // Se a prioridade do filho for maior que a do pai, troca
        if(h->vetor[i].prioridade > h->vetor[pai].prioridade){
            TrocaPassageiro(&h->vetor[i], &h->vetor[pai], m);
            i = pai;          // Sobe a referência para o pai
            pai = (i - 1) / 2; // Recalcula o novo pai
        } else {
            break; // Se já está em ordem, interrompe o laço
        }
    }
    return 1;
}
    

Passageiro RemoveHeap(Heap* h, Metricas* m) {
    Passageiro vazio = {"", -1}; // Passageiro de erro caso esteja vazio
    if (h == NULL || h->tamanho <= 0) return vazio;

    // 1. Guarda o elemento do topo (raiz) que será retornado
    Passageiro topo = h->vetor[0];

    // 2. O último elemento passa a ocupar a raiz
    h->vetor[0] = h->vetor[h->tamanho - 1];
    h->tamanho--;

    // 3. Reorganiza o heap chamando o Heapfy que já está pronto no seu código
    if (h->tamanho > 0) {
        Heapfy(h->vetor, h->tamanho, 0, m);
    }

    return topo;
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



void ComparaAlgoritmos() {
    int tamanhos[] = {1000, 5000, 10000}; // Exemplos de tamanhos de vetores para teste
    int num_testes = 3;

    printf("\n==================================================\n");
    printf("         COMPARATIVO DE DESEMPENHO DOS ALGORITMOS \n");
    printf("==================================================\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        printf("\n--- Testando com N = %d elementos ---\n", n);

        // Aloca vetores de teste
        Passageiro *v1 = (Passageiro*) malloc(n * sizeof(Passageiro));
        Passageiro *v2 = (Passageiro*) malloc(n * sizeof(Passageiro));
        Passageiro *v3 = (Passageiro*) malloc(n * sizeof(Passageiro));

        // Preenche com os mesmos dados aleatórios
        GeraVetorAleatorio(v1, n);
        // Copia para os outros vetores para garantir justiça na comparação
        for(int i=0; i<n; i++) {
            v2[i] = v1[i];
            v3[i] = v1[i];
        }

        // Inicializa as métricas
        Metricas m_heap = {0, 0};
        Metricas m_quick = {0, 0};
        Metricas m_insert = {0, 0};

        // 1. Testa HeapSort
        HeapSort(v1, n, &m_heap);
        printf("[HeapSort]    Comparações: %ld | Trocas: %ld\n", m_heap.comparacoes, m_heap.trocas);

        // 2. Testa QuickSort
        QuickSort(v2, 0, n - 1, &m_quick);
        printf("[QuickSort]   Comparações: %ld | Trocas: %ld\n", m_quick.comparacoes, m_quick.trocas);

        // 3. Testa InsertionSort (Cuidado: para N muito grande como 10000, o InsertSort demora um pouco mais!)
        if (n <= 5000) { 
            InsertSort(v3, n, &m_insert);
            printf("[Insertion]   Comparações: %ld | Trocas: %ld\n", m_insert.comparacoes, m_insert.trocas);
        } else {
            printf("[Insertion]   (Ignorado para N > 5000 por lentidão O(n^2))\n");
        }

        // Libera a memória dos testes
        free(v1);
        free(v2);
        free(v3);
    }
}



// FABIOLA //
void GeraVetorAleatorio(Passageiro* vetor, int tamanho) {
    int i;
    for(i = 0; i<tamanho; i++){
        sprintf(vetor[i].nome, "Passageiro_%d", i+1);
        vetor[i].prioridade = rand() % 100 + 1;
    }
}


// FABIOLA //
void Menu(Heap* h) {
   int opcao;
   Metricas m = {0, 0};
   
    printf("\n //////////////////////////////////");
    printf("\n ///////// VOE HEAP!  /////////////");
    printf("\n //////////////////////////////////");

    do{

        printf("\n 1 - Inserir passageiro ");
        printf("\n 2 - Remover Proximo Passageiro ");
        printf("\n 3 - Imprimir Fila de Embarque ");
        printf("\n 4 - Executar Comparativo de Algoritmos ");
        printf("\n 0 - Sair\n");

        printf("\n Digite a sua opção: ");
        scanf("%d", &opcao);

        if(opcao == 1){
            system("clear");
            printf("\n Você digitou opção 1 ");
            Passageiro p;
            printf("Digite o nome do passageiro: ");
            scanf("%s", p.nome); // Lê o nome
            printf("Digite a prioridade (inteiro): ");
            scanf("%d", &p.prioridade); // Lê a prioridade

            if (InsereHeap(h, p, &m)) {
                printf("\n[Sucesso] Passageiro inserido com sucesso!\n");
            } else {
                printf("\n[Erro] Nao foi possivel inserir (Heap lotado ou nulo).\n");
            }
            
        }
        if(opcao == 2){
            system("clear");
            printf("\n Você digitou opção 2 ");
            Passageiro removido = RemoveHeap(h, &m);
            if (removido.prioridade != -1) {
                printf("\n[Embarque] Passageiro removido do topo: %s (Prioridade: %d)\n", 
                           removido.nome, removido.prioridade);
            } else {
                printf("\n[Aviso] O Heap esta vazio!\n");
            }
            
        }
        if(opcao == 3){
            system("clear");
            printf("\n Você digitou opção 3 ");
            ImprimeHeap(h);
        }
        if(opcao == 4){
            system("clear");
            printf("\n Você digitou opção 4 ");
            ComparaAlgoritmos();
        }
    } while(opcao != 0);
} 

