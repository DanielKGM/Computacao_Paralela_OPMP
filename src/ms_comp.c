#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "array_from_file.h"
#include "print_array.h"
#include "log_execution_time.h"
#include "ms.h"

void mergesort_compartilhada(int a[], int size, int temp[], int threads) {
    if (size < 2) return;  // Caso base

    int mid = size / 2;

    if (threads > 1) {
        #pragma omp parallel
        {
            #pragma omp single nowait
            {
                #pragma omp task
                mergesort_compartilhada(a, mid, temp, threads / 2);
                
                #pragma omp task
                mergesort_compartilhada(a + mid, size - mid, temp + mid, threads - threads / 2);

                #pragma omp taskwait
                merge(a, size, temp);
            }
        }
    } else {
        mergesort_serial(a, size, temp);
    }
}

int main() {
    char filename[100];
    printf("Digite o nome do arquivo (sem .bin): ");
    scanf("%99s", filename);

    char filepath[150];
    snprintf(filepath, sizeof(filepath), "data/%s.bin", filename);

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
    mergesort_compartilhada(arr, size, temp, threads);
    double end = omp_get_wtime();

    // Calcular tempo decorrido
    double time_taken = end - start;

    // Criar nome do arquivo de log com número de threads
    char log_filename[50];
    snprintf(log_filename, sizeof(log_filename), "ms_compartilhada_%d_threads", threads);

    // Registrar tempo no log
    log_execution_time(filepath, time_taken, log_filename);

    print_array(arr, size);

    // Liberar memória
    free(arr);
    free(temp);

    return 0;
}
