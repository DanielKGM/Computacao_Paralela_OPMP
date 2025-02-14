#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "array_from_file.h"
#include "print_array.h"
#include "log_execution_time.h"
#include "merge.h"

// Merge Sort paralelo usando OpenMP
void mergesort_parallel_omp(int a[], int size, int temp[], int threads) {
    if (size < 2) return;  // Caso base: um array de 1 elemento já está ordenado

    if (threads == 1) {
        // Se só há 1 thread disponível, executa o Merge Sort sequencial
        mergesort_serial(a, size, temp);
    } else if (threads > 1) {
        int mid = size / 2;  // Divide o array ao meio

        // Cria duas seções para rodar em paralelo
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort_parallel_omp(a, mid, temp, threads / 2);  // Ordena a primeira metade
            }
            #pragma omp section
            {
                mergesort_parallel_omp(a + mid, size - mid, temp + mid, threads - threads / 2);  // Ordena a segunda metade
            }
        }

        // Mescla as duas metades ordenadas
        merge(a, size, temp);
    }
}

int main() {
    char filename[100];
    printf("Digite o nome do arquivo (sem .txt): ");
    scanf("%99s", filename);

    char filepath[150];
    snprintf(filepath, sizeof(filepath), "data/%s.txt", filename);

    int *arr;
    int size = read_array_from_file(filepath, &arr);
    if (size == -1) return 1;

    int *temp = (int *)malloc(size * sizeof(int));
    if (!temp) {
        perror("Erro ao alocar memória");
        free(arr);
        return 1;
    }

    int threads;
    printf("Digite o número de threads: ");
    scanf("%d", &threads);

    // Medir tempo do Merge Sort paralelo
    double start = omp_get_wtime();
    mergesort_parallel_omp(arr, size, temp, threads);
    double end = omp_get_wtime();

    // Calcular tempo decorrido
    double time_taken = end - start;

    // Exibir resultado
    printf("Array ordenado:\n");
    print_array(arr, size);
    printf("\n\n%.6f segundos\n", time_taken);

    // Registrar tempo no log
    log_execution_time(filepath, time_taken);

    free(arr);
    free(temp);

    return 0;
}
