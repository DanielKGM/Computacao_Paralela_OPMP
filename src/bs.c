#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include "array_from_file.h"
#include "print_array.h"
#include "log_execution_time.h"

void bubble_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    char filename[100];
    printf("Digite o nome do arquivo (sem .bin): ");
    scanf("%99s", filename);

    // Construir caminho completo
    char filepath[150];
    snprintf(filepath, sizeof(filepath), "data/%s.bin", filename);

    int *arr;
    int size = read_array_from_file(filepath, &arr);
    if (size == -1) {
        return 1;
    }

    // Medir tempo do Bubble Sort
    double start = omp_get_wtime();
    bubble_sort(arr, size);
    double end = omp_get_wtime();

    // Calcular tempo decorrido
    double time_taken = end - start;

    // Registrar tempo no log
    log_execution_time(filepath, time_taken, "bs_sequencial");

    print_array(arr, size);

    // Liberar memória
    free(arr);

    return 0;
}
