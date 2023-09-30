#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
    int key;
    char value[32];
    struct node_* left;
    struct node_* right;
} node;

node* init_node(int key, const char* value) {
    node* n = (node*)malloc(sizeof(node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    strcpy(n->value, value);
    return n;
}

void clear(node** p_current) {
    node* current = *p_current;
    if (current != NULL) {
        clear(&current->left);
        clear(&current->right);
        free(current);
        *p_current = NULL;
    }
}

node* search(node* current, int target) {
    if (current == NULL) {
        return NULL;
    }

    if (target == current->key) {
        return current;
    }

    if (target < current->key) {
        return search(current->left, target);
    } else {
        return search(current->right, target);
    }
}

void insert(node** p_current, int key, const char* value) {
    node* current = *p_current;
    if (current == NULL) {
        *p_current = init_node(key, value);
        return;
    }

    assert(key != current->key);

    if (key < current->key) {
        insert(&current->left, key, value);
    } else {
        insert(&current->right, key, value);
    }
}

node* extract_max(node** p_current) {
    node* current = *p_current;
    if (current->right == NULL) {
        *p_current = current->left;
        return current;
    }
    return extract_max(&current->right);
}

void erase(node** p_current, int key) {
    node* current = *p_current;
    assert(current != NULL);

    if (key == current->key) {
        if (current->left == NULL) {
            *p_current = current->right;
            free(current);
        } else {
            node* max = extract_max(&current->left);
            max->left = current->left;
            max->right = current->right;
            *p_current = max;
            free(current);
        }
        return;
    }

    if (key < current->key) {
        erase(&current->left, key);
    } else {
        erase(&current->right, key);
    }
}

void print(node* current, int depth) {
    if (current == NULL) {
        return;
    }
    // right
    print(current->right, depth + 1);

    // current
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("{%d, %s}\n", current->key, current->value);

    // left
    print(current->left, depth + 1);
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
    int num_keys = 15;
    int keys[15];
    for (int i = 0; i < num_keys; i++) {
        keys[i] = i;
    }
    shuffle(keys, num_keys);

    // create tree
    node* root = NULL;
    for (int i = 0; i < num_keys; i++) {
        insert(&root, keys[i], "AAA");
    }
    printf("TREE:\n");
    print(root, 0);

    // search target
    int target = 8;
    node* result = search(root, target);
    if (result != NULL) {
        printf("%d is %s\n", target, result->value);
    } else {
        printf("%d is not found\n", target);
    }

    // erase target
    erase(&root, target);
    printf("%d was deleted.\n", target);
    printf("TREE:\n");
    print(root, 0);

    // search target
    result = search(root, target);
    if (result != NULL) {
        printf("%d is %s\n", target, result->value);
    } else {
        printf("%d is not found\n", target);
    }

    clear(&root);
    return 0;
}

// 実行結果
// TREE:
//     { 67, AAA}
//   { 55, AAA}
// { 44, AAA}
//     { 42, AAA}
//         { 18, AAA}
//       { 14, AAA}
//   { 12, AAA}
//     { 6, AAA}
// 44 is AAA
// 44 was deleted.
// TREE:
//     { 67, AAA}
//   { 55, AAA}
// { 42, AAA}
//       { 18, AAA}
//     { 14, AAA}
//   { 12, AAA}
//     { 6, AAA}
// 44 is not found
