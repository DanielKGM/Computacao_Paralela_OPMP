#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array_from_file.h"

#define BUFFER_SIZE 10000  // Buffer grande o suficiente para armazenar a linha inteira

int read_array_from_file(const char *filename, int **arr) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char buffer[BUFFER_SIZE];
    if (!fgets(buffer, sizeof(buffer), file)) {
        perror("Erro ao ler o arquivo");
        fclose(file);
        return -1;
    }
    fclose(file);

    // Contar quantos números existem
    int count = 0;
    char *temp = strdup(buffer);  // Criar uma cópia para não perder os dados originais
    char *token = strtok(temp, ", ");
    while (token) {
        count++;
        token = strtok(NULL, ", ");
    }
    free(temp);  // Liberar a memória usada pela cópia

    // Alocar memória para os números
    *arr = (int *)malloc(count * sizeof(int));
    if (!(*arr)) {
        perror("Erro ao alocar memória");
        return -1;
    }

    // Preencher o array com os valores do arquivo
    count = 0;
    token = strtok(buffer, ", ");
    while (token) {
        (*arr)[count++] = atoi(token);
        token = strtok(NULL, ", ");
    }

    return count;  // Retorna o número de elementos lidos
}
