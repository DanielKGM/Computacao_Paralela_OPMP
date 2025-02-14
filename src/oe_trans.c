#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "array_from_file.h"
#include "log_execution_time.h"
#include "print_array.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void odd_even_transportation(int *arr, int n, int threads) {
    int phase, i;

    // Definir número de threads escolhidas pelo usuário
    #pragma omp parallel default(none) shared(arr, n, threads) private(phase, i) num_threads(threads)
    for (phase = 0; phase < n; phase++) {
        if (phase % 2 == 0) {
            #pragma omp for
            for (i = 1; i < n; i += 2) {
                if (arr[i - 1] > arr[i]) {
                    swap(&arr[i - 1], &arr[i]);
                }
            }
        } else {
            #pragma omp for
            for (i = 1; i < n - 1; i += 2) {
                if (arr[i] > arr[i + 1]) {
                    swap(&arr[i], &arr[i + 1]);
                }
            }
        }
    }
}

int main() {
    char filename[100];
    printf("Digite o nome do arquivo (sem .bin): ");
    scanf("%99s", filename);  // Lê o nome do arquivo sem a extensão

    // Construir caminho completo
    char filepath[150];
    snprintf(filepath, sizeof(filepath), "data/%s.bin", filename);

    int *arr;
    int size = read_array_from_file(filepath, &arr);

    if (size == -1) {
        return 1;
    }

    int threads;
    printf("Digite o número de threads: ");
    scanf("%d", &threads);

    // Medir tempo do Odd-Even Transportation Sort
    double start = omp_get_wtime();
    odd_even_transportation(arr, size, threads);
    double end = omp_get_wtime();

    // Calcular tempo decorrido
    double time_taken = end - start;

    // Criar nome do arquivo de log com número de threads
    char log_filename[50];
    snprintf(log_filename, sizeof(log_filename), "odd_even_trans_%d_threads", threads);

    // Registrar tempo no log
    log_execution_time(filepath, time_taken, log_filename);

    // Exibir resultado
    //printf("Array ordenado:\n");
    //print_array(arr, size);
    //printf("\n\n%.6f segundos\n", time_taken);

    // Liberar memória
    free(arr);

    return 0;
}
