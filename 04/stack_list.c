#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cell_ {
    int element;
    struct cell_* next;
} cell;

typedef struct
{
    cell* head;
} stack;

void clear(stack* s) {
    cell* current = s->head;
    while (current != NULL) {
        cell* next = current->next;
        free(current);
        current = next;
    }
    s->head = NULL;
}

void push(stack* s, int val) {
    cell* c = (cell*)malloc(sizeof(cell));
    c->element = val;
    c->next = s->head;
    s->head = c;
}

// 講義スライドと異なり、pop された値を返り値とします。
int pop(stack* s) {
    assert(s->head != NULL);

    int val = s->head->element;
    cell* c = s->head;
    s->head = s->head->next;
    free(c);
    return val;
}

void print(stack* s) {
    printf("LIST: [ ");
    cell* current = s->head;
    while (current != NULL) {
        printf("%d ", current->element);
        current = current->next;
    }
    printf("]\n");
}

int main() {
    stack s = {NULL};

    for (int i = 0; i < 10; i++) {
        push(&s, i);
    }
    print(&s);

    printf("POP: %d\n", pop(&s));
    print(&s);

    clear(&s);
    return 0;
}

// 実行結果
// LIST: [ 9 8 7 6 5 4 3 2 1 0 ]
// POP: 9
// LIST: [ 8 7 6 5 4 3 2 1 0 ]
