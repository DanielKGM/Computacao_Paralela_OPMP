#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>  // Para mkdir no Windows/Linux
#include <string.h>    // Para snprintf()
#include "log_execution_time.h"

#define LOGS_DIR "logs"

void log_execution_time(const char *filename, double time_taken, const char *output_file) {
    // Criar diretório "logs" se não existir
    struct stat st = {0};
    if (stat(LOGS_DIR, &st) == -1) {
        #ifdef _WIN32
            mkdir(LOGS_DIR);  // Windows
        #else
            mkdir(LOGS_DIR, 0700);  // Linux/Mac
        #endif
    }

    // Construir caminho completo do arquivo de log
    char log_filepath[256];
    snprintf(log_filepath, sizeof(log_filepath), "%s/%s.txt", LOGS_DIR, output_file);

    // Abrir arquivo no modo append
    FILE *file = fopen(log_filepath, "a");
    if (!file) {
        perror("Erro ao abrir o arquivo de logs");
        return;
    }

    // Registrar tempo e nome do arquivo no log
    fprintf(file, "%s: %.6f segundos\n", filename, time_taken);
    fclose(file);
}
