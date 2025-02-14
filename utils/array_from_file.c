#include <stdio.h>
#include <stdlib.h>
#include "array_from_file.h"

int read_array_from_file(const char *filename, int **arr) {
    FILE *file = fopen(filename, "rb");  // Abre o arquivo em modo binário
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // Descobrir o tamanho do arquivo
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Calcular a quantidade de inteiros no arquivo
    int count = file_size / sizeof(int);
    if (count == 0) {
        fprintf(stderr, "Erro: arquivo vazio ou não contém inteiros válidos.\n");
        fclose(file);
        return -1;
    }

    // Alocar memória para o array
    *arr = (int *)malloc(count * sizeof(int));
    if (!(*arr)) {
        perror("Erro ao alocar memória");
        fclose(file);
        return -1;
    }

    // Ler os inteiros do arquivo
    size_t read_count = fread(*arr, sizeof(int), count, file);
    fclose(file);

    // Verificar se houve erro na leitura
    if (read_count != count) {
        perror("Erro na leitura do arquivo");
        free(*arr);
        return -1;
    }

    return count;  // Retorna o número de elementos lidos
}
