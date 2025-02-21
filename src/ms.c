#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int size, int temp[]) {
    int mid = size / 2;
    int i = 0;
    int j = mid;
    int k = 0;

    while (i < mid && j < size) {
        if (a[i] < a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i < mid) {
        temp[k++] = a[i++];
    }
    while (j < size) {
        temp[k++] = a[j++];
    }
    for (i = 0; i < size; i++) {
        a[i] = temp[i];
    }
}

void mergesort_serial(int a[], int size, int temp[]) {
    if (size < 2) return;
    int mid = size / 2;
    mergesort_serial(a, mid, temp);
    mergesort_serial(a + mid, size - mid, temp);
    merge(a, size, temp);
}