#include <assert.h>
#include <math.h>
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

#define min(a, b) (((a) < (b)) ? (a) : (b))

void down_heap(int* array, int k, int r) {
    int v = array[k];
    while (true) {
        int j = k + k + 1;
        if (j > r) {
            break;
        }
        if (j != r && array[j + 1] > array[j]) {
            j++;
        }
        if (v >= array[j]) {
            break;
        }
        array[k] = array[j];
        k = j;
    }
    array[k] = v;
}

void heap_sort(int* array) {
    for (int i = SIZE - 1; i >= 0; i--) {
        down_heap(array, i, SIZE - 1);
    }
    for (int i = SIZE - 1; i > 0; i--) {
        swap(&array[0], &array[i]);
        down_heap(array, 0, i - 1);
    }
}

void merge(int* from, int* into, int length) {
    int start = 0;
    while (start < SIZE) {
        int i = start;
        int j = start + length;
        int k = start;
        int i_end = min(start + length, SIZE);
        int j_end = min(start + length + length, SIZE);
        while (i < i_end && j < j_end) {
            if (from[i] <= from[j]) {
                into[k++] = from[i++];
            } else {
                into[k++] = from[j++];
            }
        }
        while (i < i_end) {
            into[k++] = from[i++];
        }
        while (j < j_end) {
            into[k++] = from[j++];
        }
        start += length + length;
    }
}

void merge_sort(int* a) {
    int b[SIZE];
    int length = 1;
    while (length < SIZE) {
        merge(a, b, length);
        merge(b, a, 2 * length);
        length *= 4;
    }
}

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
    // heap_sort(array);
    merge_sort(array);
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
