#include <stdio.h>
#include <stdlib.h>
#include "ms_serial.h"

// Função que combina duas metades ordenadas do array
void merge(int a[], int size, int temp[]) {
    int mid = size / 2;  // Meio do array
    int i = 0;           // Índice para a primeira metade (esquerda)
    int j = mid;         // Índice para a segunda metade (direita)
    int k = 0;           // Índice para o array temporário

    // Enquanto houver elementos em ambas as metades
    while (i < mid && j < size) {
        if (a[i] < a[j]) {
            temp[k++] = a[i++];  // Se o elemento da esquerda for menor, copia para temp
        } else {
            temp[k++] = a[j++];  // Caso contrário, copia o da direita para temp
        }
    }

    // Copia qualquer elemento restante da metade esquerda
    while (i < mid) {
        temp[k++] = a[i++];
    }

    // Copia qualquer elemento restante da metade direita
    while (j < size) {
        temp[k++] = a[j++];
    }

    // Copia os elementos ordenados de volta para o array original
    for (i = 0; i < size; i++) {
        a[i] = temp[i];
    }
}

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