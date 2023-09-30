#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 時間計測をする際には大きな数値にしてください。
#define SIZE 10

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shell_sort(int* array) {
    int h = 1;
    while (h < SIZE) {
        h = 3 * h + 1;
    }
    while (h > 1) {
        h /= 3;
        for (int i = h; i < SIZE; i++) {
            for (int j = i - h; j >= 0; j -= h) {
                if (array[j] > array[j + h]) {
                    swap(&array[j], &array[j + h]);
                } else {
                    break;
                }
            }
        }
    }
}

void quick(int* array, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = array[(left + right) / 2];
    int i = left;
    int j = right;
    do {
        while (array[i] < pivot) {
            i++;
        }
        while (array[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(&array[i], &array[j]);
            i++;
            j--;
        }
    } while (i <= j);
    quick(array, left, j);
    quick(array, i, right);
}

void quick_sort(int* array) { quick(array, 0, SIZE - 1); }

void print(int* array) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void shuffle(int* array, int length) {
    int i = length;
    while (i > 1) {
        int j = rand() % i--;
        swap(&array[i], &array[j]);
    }
}

int main() {
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }
    shuffle(array, SIZE);

    printf("Before: ");
    print(array);

    double start_clock = (double)clock();
    // shell_sort(array);
    quick_sort(array);
    double end_clock = (double)clock();
    printf("Time  : %.8lf s\n", (end_clock - start_clock) / CLOCKS_PER_SEC);

    printf("After : ");
    print(array);

    return 0;
}

// 実行結果
// Before: 9 8 4 2 0 6 5 1 7 3
// Time  : 0.00000100 s
// After : 0 1 2 3 4 5 6 7 8 9
