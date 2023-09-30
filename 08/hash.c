#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    int key;
    char* value;
    enum {
        FREE,
        USED,
        DELETED,
    } mark;
} record;

typedef struct {
    int length;
    record records[SIZE];
} hash_table;

// 簡単なハッシュ関数
// あえて衝突するようにしている悪いアルゴリズムです。
int hash_func(int i) {
    double m = (3.14 / i) * 10000;
    return (int)m % SIZE;
}

void insert(hash_table* table, int key, char* value) {
    assert(table->length < SIZE);

    int h = hash_func(key);
    printf("hash(%d) = %d\n", key, h);
    while (table->records[h].mark == USED) {
        assert(key != table->records[h].key);
        h = (h + 1) % SIZE;
    }
    record rec = {key, value, USED};
    table->records[h] = rec;
    table->length++;
}

// target と一致する record を探索し
// 見つかった場合はそのポインタを返します。
// 見つからなかった場合は NULL を返します。
record* search(hash_table* table, int target) {
    int pos = hash_func(target);
    while (table->records[pos].mark == USED &&
           target != table->records[pos].key) {
        pos = (pos + 1) % SIZE;
    }
    if (table->records[pos].mark == USED) {
        return &table->records[pos];
    }
    return NULL;
}

void print(hash_table* table) {
    printf("TABLE:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("  {%d, %s, %d}\n", table->records[i].key,
               table->records[i].value, table->records[i].mark);
    }
}

int main() {
    hash_table table = {0};
    insert(&table, 1, "AA");
    insert(&table, 2, "BB");
    insert(&table, 3, "CC");
    insert(&table, 4, "DD");
    print(&table);

    int target = 3;
    record* rec = search(&table, target);
    if (rec) {
        printf("%d is %s\n", target, rec->value);
    } else {
        printf("%d is NULL\n", target);
    }

    target = 5;
    rec = search(&table, target);
    if (rec) {
        printf("%d is %s\n", target, rec->value);
    } else {
        printf("%d is NULL\n", target);
    }

    return 0;
}

// 実行結果
// hash(1) = 0
// hash(2) = 0
// hash(3) = 6
// hash(4) = 0
// TABLE:
//   {1, AA, 1}
//   {2, BB, 1}
//   {4, DD, 1}
//   {0, (null), 0}
//   {0, (null), 0}
//   {0, (null), 0}
//   {3, CC, 1}
//   {0, (null), 0}
//   {0, (null), 0}
//   {0, (null), 0}
// 3 is CC
// 5 is NULL
