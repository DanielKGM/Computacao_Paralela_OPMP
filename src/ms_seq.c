#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "array_from_file.h"
#include "print_array.h"
#include "log_execution_time.h"
#include "ms.h"

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

    int *temp = (int *)malloc(size * sizeof(int));
    if (!temp) {
        perror("Erro ao alocar memória");
        free(arr);
        return 1;
    }

    // Medir tempo do Merge Sort
    double start = omp_get_wtime();
    mergesort_serial(arr, size, temp);
    double end = omp_get_wtime();

    // Calcular tempo decorrido
    double time_taken = end - start;

    // Registrar tempo no log
    log_execution_time(filepath, time_taken, "ms_sequencial");

    print_array(arr, size);

    // Liberar memória
    free(arr);
    free(temp);

    return 0;
}