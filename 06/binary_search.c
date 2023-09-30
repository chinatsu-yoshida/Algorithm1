#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_RECORDS 1000

typedef struct {
    int key;
    char value[32];
} record;

typedef struct {
    int length;
    record records[MAX_NUM_RECORDS];
} table;

// key 以下となる値が現れる最大の index を返します。
// もし条件を満たす値が存在しない場合は -1 を返します。
int search(table* tab, int target) {
    int low = 0;
    int high = tab->length - 1;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (target < tab->records[middle].key) {
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }
    return high;
}

void insert(table* tab, record rec) {
    assert(tab->length < MAX_NUM_RECORDS);

    // 順序が正しく保たれるように、正しい挿入位置を計算します
    int index = search(tab, rec.key);

    // before: [0 1 2 4]
    // insert: 3 (index = 2)
    // after : [0 1 2   4]
    for (int i = tab->length; i > index + 1; i--) {
        tab->records[i] = tab->records[i - 1];
    }

    // before: [0 1 2   4]
    // after : [0 1 2 3 4]
    tab->records[index + 1] = rec;
    tab->length++;
}

void erase(table* tab, int pos) {
    // before: [0 1 2 3 4 5]
    // erase: 3 (index = 3)
    // after : [0 1 2 4 5]
    for (int i = pos; i < tab->length - 1; i++) {
        tab->records[i] = tab->records[i + 1];
    }
    tab->length--;
}

void print(table* tab) {
    printf("[ ");
    for (int i = 0; i < tab->length; i++) {
        printf("{%d, %s} ", tab->records[i].key, tab->records[i].value);
    }
    printf("]\n");
}

// 入力をシャッフルするために用意した本題とは関係ない関数です。
void shuffle(int* array, int length) {
    int i = length;
    while (i > 1) {
        int j = rand() % i--;
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

int main() {
    // create inputs
    int num_keys = 5;
    int keys[5];
    for (int i = 0; i < num_keys; i++) {
        keys[i] = i;
    }
    shuffle(keys, num_keys);

    table tab = {0};
    for (int i = 0; i < num_keys; i++) {
        record rec = {keys[i], "AAA"};
        insert(&tab, rec);
    }
    print(&tab);

    // search 3
    int target = 3;
    int index = search(&tab, target);
    if (index != -1 && tab.records[index].key == target) {
        printf("%d was %s\n", target, tab.records[index].value);
    } else {
        printf("%d was NOT FOUND.\n", target);
    }

    // erase 3
    printf("erase: %d\n", target);
    erase(&tab, index);
    print(&tab);

    // search 3
    index = search(&tab, target);
    if (index != -1 && tab.records[index].key == target) {
        printf("%d was %s\n", target, tab.records[index].value);
    } else {
        printf("%d was NOT FOUND.\n", target);
    }

    return 0;
}

// 実行結果
// [ {0, AAA} {1, AAA} {2, AAA} {3, AAA} {4, AAA} ]
// 3 was AAA
// erase: 3
// [ {0, AAA} {1, AAA} {2, AAA} {4, AAA} ]
// 3 was NOT FOUND.
