#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record_ {
    int key;
    char value[32];
    struct record_* next;
} record;

typedef struct {
    record* header;
    record* sentinel;
} table;

record* init_record(int key, const char* value) {
    record* rec = (record*)malloc(sizeof(record));
    rec->next = NULL;
    rec->key = key;
    strcpy(rec->value, value);
    return rec;
}

void clear(table* tab) {
    record* current = tab->header->next;
    while (current != tab->sentinel) {
        record* next = current->next;
        free(current);
        current = next;
    }

    free(tab->header);
    free(tab->sentinel);
    tab->header = NULL;
    tab->sentinel = NULL;
}

record* search_previous(table* tab, int target) {
    tab->sentinel->key = target;
    record* previous = tab->header;
    record* current = tab->header->next;
    while (target != current->key) {
        previous = current;
        current = current->next;
    }
    bool found = current != tab->sentinel;

    // コメントアウトを外すと自己再構成リストになります。
    // if (found) {
    //   previous->next = current->next;
    //   insert_head(tab, current);
    // }
    return found ? previous : NULL;
}

void insert_head(table* tab, record* rec) {
    rec->next = tab->header->next;
    tab->header->next = rec;
}

void erase_next(record* previous) {
    record* current = previous->next;
    previous->next = current->next;
    free(current);
}

void cli_insert_head(table* tab) {
    printf("Type in a key (>= 0) and a field. (example: \"100 XX\")\n");
    while (true) {
        record* rec = init_record(-1, "");
        scanf("%d %s", &rec->key, rec->value);

        if (search_previous(tab, rec->key) != NULL) {
            printf("The key is already used.\n");
        } else {
            insert_head(tab, rec);
            return;
        }
    }
}

void print(table* tab) {
    printf("TABLE: [ ");
    record* current = tab->header->next;
    while (current != tab->sentinel) {
        printf("{%d, %s} ", current->key, current->value);
        current = current->next;
    }
    printf("]\n");
}

int main() {
    // create table
    table tab;
    tab.sentinel = init_record(-1, "");
    tab.header = init_record(-1, "");
    tab.header->next = tab.sentinel;

    insert_head(&tab, init_record(5, "EEE"));
    insert_head(&tab, init_record(2, "BBB"));
    insert_head(&tab, init_record(1, "AAA"));
    insert_head(&tab, init_record(3, "CCC"));
    insert_head(&tab, init_record(4, "DDD"));
    print(&tab);

    // insert user input
    cli_insert_head(&tab);
    print(&tab);

    // search 3
    int target = 3;
    record* previous = search_previous(&tab, target);
    if (previous != NULL) {
        printf("%d was %s\n", target, previous->next->value);
    } else {
        printf("%d was NOT FOUND\n", target);
    }

    // erase 3
    erase_next(previous);
    print(&tab);

    // search 3
    previous = search_previous(&tab, target);
    if (previous != NULL) {
        printf("%d was %s\n", target, previous->next->value);
    } else {
        printf("%d was NOT FOUND\n", target);
    }

    clear(&tab);
    return 0;
}

// 実行結果
// TABLE: [ {4, DDD} {3, CCC} {1, AAA} {2, BBB} {5, EEE} ]
// Type in a key (>= 0) and a field. (example: "100 XX")
// 100 XXX
// TABLE: [ {100, XXX} {4, DDD} {3, CCC} {1, AAA} {2, BBB} {5, EEE} ]
// 3 was CCC
// TABLE: [ {100, XXX} {4, DDD} {1, AAA} {2, BBB} {5, EEE} ]
// 3 was NOT FOUND
