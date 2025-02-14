#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array_from_file.h"
#include "print_array.h"
#include "log_execution_time.h"
#include "merge.h"

// Implementação do MergeSort recursivo
void mergesort_serial(int a[], int size, int temp[]) {
    if (size < 2) return;  // Caso base: um array de 1 elemento já está ordenado

    int mid = size / 2;  // Divide o array em duas partes

    // Chamada recursiva para ordenar a primeira metade
    mergesort_serial(a, mid, temp);

    // Chamada recursiva para ordenar a segunda metade
    mergesort_serial(a + mid, size - mid, temp);

    // Mescla as duas metades ordenadas
    merge(a, size, temp);
}

int main() {
    char filename[100];
    printf("Digite o nome do arquivo (sem .txt): ");
    scanf("%99s", filename);  // Lê o nome do arquivo sem a extensão

    // Construir caminho completo
    char filepath[150];
    snprintf(filepath, sizeof(filepath), "data/%s.txt", filename);

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
    clock_t start = clock();
    mergesort_serial(arr, size, temp);
    clock_t end = clock();

    // Calcular tempo decorrido
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Exibir resultado
    printf("Array ordenado:\n");
    print_array(arr, size);
    printf("\n\n%.6f segundos\n", time_taken);

    // Registrar tempo no log
    log_execution_time(filepath, time_taken);

    // Liberar memória
    free(arr);
    free(temp);

    return 0;
}