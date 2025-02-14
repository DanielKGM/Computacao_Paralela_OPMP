#include <stdio.h>
#include "print_array.h"

void print_array(int *arr, int size) {
    int exibir;
    printf("Exibir resultado? (1=sim): ");
    scanf("%d", &exibir);
    if( exibir == 1){
        for (int i = 0; i < size; i++) {
            printf("%d", arr[i]);
            if (i < size - 1) {
                printf(", ");
            }
        }
    }
}
