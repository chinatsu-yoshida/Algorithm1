#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

typedef struct {
    int head;
    int tail;
    int count;
    int elements[SIZE];
} queue;

void clear(queue* q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
}

bool empty(queue* q) {
    return q->count == 0;
}

void enqueue(queue* q, int val) {
    assert(q->count < SIZE);

    q->elements[q->tail] = val;
    q->tail++;
    if (q->tail >= SIZE) {
        q->tail = 0;
    }
    q->count++;
}

// 講義スライドと異なり、dequeue された値を返り値とします。
int dequeue(queue* q) {
    assert(q->count > 0);

    int val = q->elements[q->head];
    q->head++;
    if (q->head >= SIZE) {
        q->head = 0;
    }
    q->count--;
    return val;
}

void print(queue* q) {
    printf("QUEUE: [ ");
    int index = q->head;
    for (int count = 0; count < q->count; count++) {
        printf("%d ", q->elements[index]);
        index = (index + 1) % SIZE;
    }
    printf("]\n");

    // SIZE を 8 程度にして操作の内容を変更して
    // リングバッファの様子を確認してみましょう
    // printf("ELEMENTS: [ ");
    // for(int i = 0; i < SIZE; i++ )
    // {
    //   printf("%d ", q->elements[i] );
    // }
    // printf("]\n");
}

int main() {
    queue q = {0, 0, 0, {0}};

    for (int i = 0; i < 10; i++) {
        enqueue(&q, i);
    }
    print(&q);

    printf("DEQUEUE: %d\n", dequeue(&q));
    print(&q);

    clear(&q);
    print(&q);
    return 0;
}

// 実行結果
// QUEUE: [ 0 1 2 3 4 5 6 7 8 9 ]
// DEQUEUE: 0
// QUEUE: [ 1 2 3 4 5 6 7 8 9 ]
// QUEUE: [ ]
