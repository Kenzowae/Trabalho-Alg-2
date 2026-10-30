# Relatório — VOE HEAP

## Desenvolvimento em dupla

O trabalho foi desenvolvido em conjunto pela dupla, por meio de reuniões nas quais discutimos a estrutura do programa, adaptamos o código e revisamos o funcionamento das funções. A implementação foi organizada em torno de uma fila de embarque com prioridades, utilizando os algoritmos estudados em sala de aula como base. Alguns deles precisaram ser adaptados para trabalhar com registros de passageiros, com os índices dos vetores em C e com a contagem das operações realizadas.

## Estrutura e funções

O programa utiliza três estruturas: `Passageiro`, que guarda nome e prioridade; `Heap`, que armazena o vetor, o tamanho atual e a capacidade; e `Metricas`, que registra comparações e trocas. As declarações ficam em `voeheap.h` e a implementação em `voeheap.c`. A fila é um max-heap: quanto maior o valor da prioridade, mais cedo o passageiro é removido para embarque.

- `main` e `InicHeap`: criam a fila com capacidade para 50 passageiros. A inicialização aloca a estrutura e o vetor; ao encerrar, a memória é liberada.
- `InsereHeap`: adiciona o passageiro no final e compara sua prioridade com a do pai, realizando trocas para cima até recuperar a propriedade do heap.
- `RemoveHeap`: guarda o passageiro da raiz, coloca o último registro em seu lugar e chama `Heapfy` para reorganizar a fila. Quando vazia, retorna um registro com prioridade −1.
- `Heapfy`: compara um nó com seus filhos, troca com o de maior prioridade e continua recursivamente. Foi adaptada para receber diretamente um vetor, permitindo seu reaproveitamento no HeapSort.
- `ChecaHeap`, `ConstruirHeap` e `ImprimeHeap`: verificam a propriedade do max-heap, constroem o heap a partir de um vetor e exibem os passageiros, respectivamente. A impressão mostra a organização interna da estrutura, não uma ordenação completa de embarque.
- `HeapSort`: constrói um max-heap e move sucessivamente o maior elemento para o fim do vetor, produzindo ordem crescente de prioridade.
- `MedianaDeTres`, `Particiona` e `QuickSort`: escolhem o pivô entre início, meio e fim, separam os elementos em torno dele e ordenam recursivamente os dois lados.
- `InsertSort`: insere cada passageiro na posição correta da parte já ordenada. O algoritmo foi ajustado para começar no índice zero, sem usar uma posição extra como sentinela e sem acessar posições fora do vetor.
- `TrocaPassageiro`: troca os registros completos, mantendo nome e prioridade associados, e atualiza a métrica de trocas.
- `GeraVetorAleatorio` e `ComparaAlgoritmos`: geram prioridades de 1 a 100 e executam os algoritmos sobre cópias dos mesmos dados, com contadores separados.
- `Menu`: integra as operações de inserção, remoção, impressão e comparação dos algoritmos.

Na revisão, também foram alinhados os protótipos do cabeçalho com as funções implementadas, corrigida a alocação do vetor para comportar toda a capacidade e completada a contagem das três comparações da mediana de três. Os comentários foram concentrados acima das funções para facilitar a leitura.

## Resultados obtidos

O programa foi compilado com GCC, usando `-std=c11 -Wall -Wextra -Wpedantic`, sem avisos. Foram verificados o limite de 50 passageiros, a rejeição de inserção em fila cheia, a remoção em fila vazia e a manutenção do max-heap após inserções e remoções. Em um teste pelo menu, passageiros com prioridades 2, 9 e 5 foram removidos na sequência 9, 5 e 2.

Os três algoritmos produziram prioridades em ordem crescente nos testes com vetores vazios, unitários, aleatórios, crescentes, decrescentes e com prioridades iguais, incluindo tamanhos de até 10.000 elementos. Uma execução do comparativo do menu apresentou os seguintes resultados:

| Quantidade | HeapSort: comparações / trocas | QuickSort: comparações / trocas | Insertion: comparações / movimentações |
|---|---:|---:|---:|
| 1.000 | 16.786 / 9.015 | 14.360 / 10.201 | 249.591 / 249.593 |
| 5.000 | 107.364 / 56.789 | 176.580 / 153.472 | 6.230.928 / 6.230.933 |
| 10.000 | 234.189 / 123.260 | 598.277 / 556.735 | Não executado pelo menu |

Os números correspondem a uma execução com os dados pseudoaleatórios do programa, sem medição de tempo. No Insertion Sort, o contador chamado `trocas` contabiliza deslocamentos e inserções; portanto, não representa a mesma operação de troca de dois registros usada nos outros algoritmos.

Nessa execução, o QuickSort realizou menos comparações com 1.000 elementos, enquanto o HeapSort apresentou menos comparações e trocas nos dois tamanhos maiores. As prioridades repetidas podem gerar partições desequilibradas no QuickSort implementado, mesmo com a mediana de três. O Insertion Sort apresentou crescimento muito maior no número de operações, coerente com seu comportamento quadrático no caso médio; por isso, o menu não o executa acima de 5.000 elementos. A fila permite retirar o passageiro de maior prioridade, mas não garante ordem de chegada entre passageiros com prioridades iguais.
