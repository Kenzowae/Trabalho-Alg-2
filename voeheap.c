#include "voeheap.h"

/* Inicializa a fila com capacidade para 50 passageiros, executa o menu e libera a memória. */
int main(void){
    int capacidade_inicial = 50;
    Heap *meuHeap = InicHeap(capacidade_inicial);
    if (meuHeap == NULL) {
        printf("Erro fatal: Nao foi possivel alocar o heap.\n");
        return EXIT_FAILURE;
    }
    Menu(meuHeap);
    free(meuHeap->vetor);
    free(meuHeap);
    return EXIT_SUCCESS;
}

/* Aloca a estrutura e o vetor de passageiros, iniciando um heap vazio. */
Heap* InicHeap(int capacidade) {
    if (capacidade <= 0)
        return NULL;
    Heap *h = (Heap*) malloc(sizeof(Heap));
    if (!h)
        return NULL;
    h->vetor = (Passageiro*) malloc((size_t)capacidade * sizeof(Passageiro));
    if (!(h->vetor)) {
        free(h);
        return NULL;
    }

    h->tamanho = 0;
    h->capacidade = capacidade;
    return h;
}

/* Insere no final do vetor e sobe o passageiro até restabelecer o max-heap. */
int InsereHeap(Heap* h, Passageiro p, Metricas* m) {

    if(h == NULL){
    printf("\n O heap não existe!");
    return 0;
    }

    if(h->tamanho >= h->capacidade){
        printf("\n O heap está lotado");
        return 0;
    }

    int i = h->tamanho;
    h->vetor[i] = p;

    h->tamanho++;

    int pai = (i-1)/2;

      while(i > 0){
        if (m) m->comparacoes++;

        if(h->vetor[i].prioridade > h->vetor[pai].prioridade){
            TrocaPassageiro(&h->vetor[i], &h->vetor[pai], m);
            i = pai;
            pai = (i - 1) / 2;
        } else {
            break;
        }
    }
    return 1;
}

/* Retira o passageiro de maior prioridade e reorganiza a raiz com Heapfy. */
Passageiro RemoveHeap(Heap* h, Metricas* m) {
    Passageiro vazio = {"", -1};
    if (h == NULL || h->tamanho <= 0) return vazio;

    Passageiro topo = h->vetor[0];

    h->vetor[0] = h->vetor[h->tamanho - 1];
    h->tamanho--;

    if (h->tamanho > 0) {
        Heapfy(h->vetor, h->tamanho, 0, m);
    }

    return topo;
}

/* Restaura o max-heap trocando o nó com o filho de maior prioridade e descendo recursivamente. */
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

/* Verifica se cada pai possui prioridade maior ou igual à de seus filhos. */
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

/* Exibe o vetor do heap; a exibição não representa uma lista totalmente ordenada. */
void ImprimeHeap(Heap* h) {
    printf("\n--- Fila de Embarque ---\n");

    for(int i = 0; i < h->tamanho; i++)
        printf("Passageiro %s | Prioridade: %d\n", h->vetor[i].nome, h->vetor[i].prioridade );
}

/* Transforma os dados do vetor em max-heap, reorganizando dos pais até a raiz. */
void ConstruirHeap(Heap* h) {
    if (!h || !h->vetor || h->tamanho <= 1)
        return;

    for(int i = (h->tamanho/2); i >= 0; i--)
        Heapfy(h->vetor, h->tamanho, i, NULL);
}

/* Ordena por prioridade crescente, construindo um max-heap e extraindo seus maiores valores. */
void HeapSort(Passageiro* vetor, int n, Metricas* m) {
    int i;
    for(i = n / 2 - 1; i>= 0; i--)
        Heapfy(vetor, n, i, m);

    for (i = n - 1; i > 0; i--){
        TrocaPassageiro(&vetor[0], &vetor[i], m);
        Heapfy(vetor, i, 0, m);
    }
}

/* Escolhe a mediana entre início, meio e fim como pivô e a posiciona no fim. */
int MedianaDeTres(Passageiro* vetor, int inicio, int fim, Metricas* m) {
    int meio = (inicio + fim)/ 2;

    if (m) m->comparacoes++;
    if (vetor[inicio].prioridade > vetor[meio].prioridade)
        TrocaPassageiro(&vetor[inicio], &vetor[meio], m);

    if (m) m->comparacoes++;
    if (vetor[inicio].prioridade > vetor[fim].prioridade)
        TrocaPassageiro(&vetor[inicio], &vetor[fim], m);

    if (m) m->comparacoes++;
    if (vetor[meio].prioridade > vetor[fim].prioridade)
        TrocaPassageiro(&vetor[meio], &vetor[fim], m);

    TrocaPassageiro(&vetor[meio], &vetor[fim], m);

    return fim;
}

/* Separa as prioridades em torno do pivô e devolve sua posição definitiva. */
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

/* Ordena por prioridade crescente, particionando e ordenando os dois lados recursivamente. */
void QuickSort(Passageiro* vetor, int inicio, int fim, Metricas* m) {
    if (inicio < fim){
        int posicao_pivo = Particiona(vetor, inicio, fim, m);
        QuickSort(vetor, inicio, posicao_pivo - 1, m);
        QuickSort(vetor, posicao_pivo + 1, fim, m);
    }
}

/* Ordena por inserção com índices a partir de zero; contabiliza deslocamentos e inserções como trocas. */
void InsertSort(Passageiro* vetor, int n, Metricas* m) {
    for (int i = 1; i < n; i++) {
        Passageiro aux = vetor[i];
        int j = i - 1;

        while (j >= 0) {
            if (m) m->comparacoes++;
            if (vetor[j].prioridade <= aux.prioridade)
                break;
            vetor[j + 1] = vetor[j];
            if (m) m->trocas++;
            j--;
        }
        vetor[j + 1] = aux;
        if (m) m->trocas++;
    }
}

/* Troca registros completos de passageiros e incrementa o contador de trocas. */
void TrocaPassageiro(Passageiro* a, Passageiro* b, Metricas* m) {
    Passageiro passageiro_temp = *a;
    *a = *b;
    *b = passageiro_temp;
    if (m)
        m->trocas++;
}

/* Compara os algoritmos com cópias dos mesmos dados e registra comparações e trocas. */
void ComparaAlgoritmos(void) {
    int tamanhos[] = {1000, 5000, 10000};
    int num_testes = 3;

    printf("\n==================================================\n");
    printf("         COMPARATIVO DE DESEMPENHO DOS ALGORITMOS \n");
    printf("==================================================\n");

    for (int t = 0; t < num_testes; t++) {
        int n = tamanhos[t];
        printf("\n--- Testando com N = %d elementos ---\n", n);

        Passageiro *v1 = (Passageiro*) malloc(n * sizeof(Passageiro));
        Passageiro *v2 = (Passageiro*) malloc(n * sizeof(Passageiro));
        Passageiro *v3 = (Passageiro*) malloc(n * sizeof(Passageiro));

        if (!v1 || !v2 || !v3) {
            free(v1);
            free(v2);
            free(v3);
            printf("Erro ao alocar vetores de teste.\n");
            return;
        }
        GeraVetorAleatorio(v1, n);

        for(int i=0; i<n; i++) {
            v2[i] = v1[i];
            v3[i] = v1[i];
        }

        Metricas m_heap = {0, 0};
        Metricas m_quick = {0, 0};
        Metricas m_insert = {0, 0};

        HeapSort(v1, n, &m_heap);
        printf("[HeapSort]    Comparações: %ld | Trocas: %ld\n", m_heap.comparacoes, m_heap.trocas);

        QuickSort(v2, 0, n - 1, &m_quick);
        printf("[QuickSort]   Comparações: %ld | Trocas: %ld\n", m_quick.comparacoes, m_quick.trocas);

        if (n <= 5000) {
            InsertSort(v3, n, &m_insert);
            printf("[Insertion]   Comparações: %ld | Trocas: %ld\n", m_insert.comparacoes, m_insert.trocas);
        } else {
            printf("[Insertion]   (Ignorado para N > 5000 por lentidão O(n^2))\n");
        }

        free(v1);
        free(v2);
        free(v3);
    }
}

/* Preenche o vetor com nomes de teste e prioridades pseudoaleatórias entre 1 e 100. */
void GeraVetorAleatorio(Passageiro* vetor, int tamanho) {
    int i;
    for(i = 0; i<tamanho; i++){
        sprintf(vetor[i].nome, "Passageiro_%d", i+1);
        vetor[i].prioridade = rand() % 100 + 1;
    }
}

/* Permite inserir, remover e consultar passageiros, além de executar o comparativo. */
void Menu(Heap* h) {
   int opcao;
   Metricas m = {0, 0};

    printf("\n========== VOE HEAP! ==========\n");

    do{

        printf("\n 1 - Inserir passageiro ");
        printf("\n 2 - Remover Proximo Passageiro ");
        printf("\n 3 - Imprimir Fila de Embarque ");
        printf("\n 4 - Executar Comparativo de Algoritmos ");
        printf("\n 0 - Sair\n");

        printf("\n Digite a sua opção: ");
        if (scanf("%d", &opcao) != 1)
            return;

        if(opcao == 1){

            printf("\n Você digitou opção 1 ");
            Passageiro p;
            printf("Digite o nome do passageiro: ");
            if (scanf("%49s", p.nome) != 1) return;
            printf("Digite a prioridade (inteiro): ");
            if (scanf("%d", &p.prioridade) != 1) return;

            if (InsereHeap(h, p, &m)) {
                printf("\n[Sucesso] Passageiro inserido com sucesso!\n");
            } else {
                printf("\n[Erro] Nao foi possivel inserir (Heap lotado ou nulo).\n");
            }

        }
        if(opcao == 2){

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

            printf("\n Você digitou opção 3 ");
            ImprimeHeap(h);
        }
        if(opcao == 4){

            printf("\n Você digitou opção 4 ");
            ComparaAlgoritmos();
        }
    } while(opcao != 0);
}

