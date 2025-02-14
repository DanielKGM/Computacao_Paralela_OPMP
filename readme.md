# Comandos Windows GCC Compiler

## Merge Sort (Sequencial)

```
gcc -o ms_sequencial.exe src/ms_sequencial.c utils/array_from_file.c utils/print_array.c utils/log_execution_time.c utils/merge.c -I utils
```

## Merge Sort (Memória Compartilhada)

Implementação feita com o OpenMP, é necessário o argumento -fopenmp

```
gcc -o ms_compartilhada.exe src/ms_compartilhada.c utils/array_from_file.c utils/print_array.c utils/log_execution_time.c utils/merge.c -I utils -fopenmp
```
