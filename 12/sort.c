#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 時間計測をする際には大きな数値にしてください。
#define SIZE 10
#define M 5

// 配列の要素は [0, m-1] の範囲とします。
void count_sort(int* a) {
    int count[M + 1] = {0};
    for (int i = 0; i < SIZE; i++) {
        count[a[i]]++;
    }

    for (int i = 0; i < M; i++) {
        count[i + 1] += count[i];
    }

    int b[SIZE];
    for (int i = SIZE - 1; i >= 0; i--) {
        int j = --count[a[i]];
        b[j] = a[i];
    }

    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i];
    }
}

// 配列の要素は [0, m-1] の範囲とします。
void bin_sort(int* a) {
    int head[M];
    for (int i = 0; i < M; i++) {
        head[i] = -1;
    }

    int next[SIZE];
    for (int i = SIZE - 1; i >= 0; i--) {
        int value = a[i];
        next[i] = head[value];
        head[value] = i;
    }

    int b[SIZE];
    int i = 0;
    for (int j = 0; j < M; j++) {
        int p = head[j];
        while (p != -1) {
            b[i++] = a[p];
            p = next[p];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        a[i] = b[i];
    }
}

void print(int* array) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int array[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % M;
    }

    printf("Before: ");
    print(array);

    double start_clock = (double)clock();

    count_sort(array);
    // bin_sort(array);

    double end_clock = (double)clock();
    printf("Time  : %.8lf s\n", (end_clock - start_clock) / CLOCKS_PER_SEC);

    printf("After : ");
    print(array);

    return 0;
}

// 実行結果
// Before: 1 7 4 0 9 4 8 8 2 4
// Time : 0.00000000 s
// After : 0 1 2 4 4 4 7 8 8 9
