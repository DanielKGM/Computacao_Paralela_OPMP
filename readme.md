# Implementação e Comparação de Algoritmos de Ordenação

## 1. Implementação dos Algoritmos

Este repositório providencia as seguintes implementações de algoritmos de ordenação:

### a) Mergesort

- Implementação sequencial do Mergesort

### b) Mergesort Paralelo (Memória Compartilhada)

- Implementação utilizando memória compartilhada

### c) Mergesort Paralelo (Memória Distribuída)

Implementação utilizando memória distribuída

- Referência: [Chapman University - Mergesort](https://digitalcommons.chapman.edu/cgi/viewcontent.cgi?article=1017&context=scs_books)

### d) Odd-Even Transposition Sort Paralelo

- Referência: Livro do Pacheco, _Program 5.5: Second OpenMP implementation of odd-even sort_, página 236.

### e) Odd-Even Mergesort Paralelo

- Referências:
  - [Slides ITCS4145](https://webpages.charlotte.edu/abw/coit-grid01.uncc.edu/ITCS4145F12/slides10.ppt)
  - [Odd-Even Mergesort](https://hwlang.de/algorithmen/sortieren/networks/oemen.htm)

## 2. Experimento de Comparação

Os diretórios `/logs` e `/data` servem para realizar um experimento de comparação das implementações, aferindo o tempo médio de processamento em **10 execuções** de diversas situações.

## 3. Conjunto de Dados

Os algoritmos devem ser testados com vetores de números inteiros de diferentes tamanhos:

- **10 milhões** de elementos (_Half_)
- **100 milhões** de elementos (_Original_)
- **1 bilhão** de elementos (_Double_)

## 4. Testes com Diferentes Números de Processos/Threads

Os logs registram as seguintes escalas de processos/threads:

- **(a) Sequencial:** 1 processo/thread
- **(b) Paralelo 2:** 2 processos/threads
- **(c) Paralelo 3:** 3 processos/threads
- **(d) Paralelo 4:** 4 processos/threads
- **(e) Outras configurações**, caso o equipamento permita.

# Comandos Windows GCC Compiler

## Merge Sort (Sequencial)

`-fopenmp` é utilizado apenas para a função omp_get_wtime()

```
gcc -o ms_sequencial.exe src/ms_seq.c utils/array_from_file.c utils/print_array.c utils/log_execution_time.c src/ms.c -I utils -fopenmp
```

## Merge Sort (Memória Compartilhada)

```
gcc -o ms_compartilhada.exe src/ms_comp.c utils/array_from_file.c utils/print_array.c utils/log_execution_time.c src/ms.c -I utils -fopenmp
```

## BubbleSort (Sequencial)

```
gcc -o bubblesort.exe src/bs.c utils/array_from_file.c utils/print_array.c utils/log_execution_time.c -I utils -fopenmp
```

## Odd Even Transposition (Memória Compartilhada)

```
gcc -o oe_transposition.exe src/oe_trans.c utils/array_from_file.c utils/print_array.c utils/log_execution_time.c -I utils -fopenmp
```
