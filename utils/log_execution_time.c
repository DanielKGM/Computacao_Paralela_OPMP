#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>  // Para mkdir no Windows/Linux
#include "log_execution_time.h"

#define LOGS_DIR "logs"
#define LOG_FILE "logs/ms_sequencial.txt"

void log_execution_time(const char *filename, double time_taken) {
    // Criar diretório "logs" se não existir
    struct stat st = {0};
    if (stat(LOGS_DIR, &st) == -1) {
        #ifdef _WIN32
            mkdir(LOGS_DIR);  // Windows
        #else
            mkdir(LOGS_DIR, 0700);  // Linux/Mac
        #endif
    }

    // Abrir arquivo no modo append
    FILE *file = fopen(LOG_FILE, "a");
    if (!file) {
        perror("Erro ao abrir o arquivo de logs");
        return;
    }

    // Registrar tempo e nome do arquivo no log
    fprintf(file, "%s: %.6f segundos\n", filename, time_taken);
    fclose(file);
}
