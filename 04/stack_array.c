#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

// C 言語の配列は zero origin であることから
// 講義スライドの sp と 本サンプルの length は
// 役割が若干異なります。それによって push や
// pop の実装も違いがあるので注意してください。
typedef struct {
    int length;
    int elements[SIZE];
} stack;

void clear(stack* stack) {
    stack->length = 0;
}

void push(stack* stack, int val) {
    assert(stack->length < SIZE);

    stack->elements[stack->length] = val;
    stack->length++;
}

// 講義スライドと異なり、pop された値を返り値とします。
int pop(stack* stack) {
    assert(stack->length != 0);

    stack->length--;
    return stack->elements[stack->length];
}

void print(stack* s) {
    printf("ELEMENTS: [ ");
    for (int i = s->length - 1; i >= 0; i--) {
        printf("%d ", s->elements[i]);
    }
    printf("]\n");
    printf("STACK POINTER: %d\n", s->length);
}

int main() {
    stack s = {0, {0}};

    for (int i = 0; i < 10; i++) {
        push(&s, i);
    }
    print(&s);

    printf("POP: %d\n", pop(&s));
    print(&s);

    clear(&s);
    print(&s);

    return 0;
}

// 実行結果
// ELEMENTS: [ 9 8 7 6 5 4 3 2 1 0 ]
// STACK POINTER: 10
// POP: 9
// ELEMENTS: [ 8 7 6 5 4 3 2 1 0 ]
// STACK POINTER: 9
// ELEMENTS: [ ]
// STACK POINTER: 0
