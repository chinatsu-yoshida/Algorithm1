#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// list では 可読性のために node と list を別の構造体に
// していました。しかし、別の構造体にすると統一的な再帰関数
// を定義できないというデメリットがあります。木構造では
// 再帰関数が多用されるため構造体を1つにします。また、
// C言語において typedef node* tree; と書くとスライド同様
// に tree を扱えますが、次のコメントで言及する pointer to
// pointer において混乱を招くため、tree は定義しません。
typedef struct node_ {
    char element;
    struct node_* left;
    struct node_* right;
} node;

node* init_node(char element) {
    node* n = (node*)malloc(sizeof(node));
    n->element = element;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// list では node と別の構造体にすることで pointer
// to pointer と dereference を回避していました。
// 木構造では、これらを回避するとかなりコードが肥大化
// してしまうため、採用することにします。
// pointer to pointer はその名の通り pointer を指す
// pointer です。単なる pointer はそれが指すインスタンス
// の中身を変更できます。それに対して pointer to pointer
// は pointer の中身、つまり pointer が指すインスタンス
// そのものを、別のインスタンス、または NULL に変更できます。
void clear(node** p_current) {
    node* current = *p_current;
    if (current != NULL) {
        clear(&current->left);
        clear(&current->right);
        free(current);
        *p_current = NULL;
    }
}

void pre_order(node* p) {
    if (p != NULL) {
        printf("%c ", p->element);
        pre_order(p->left);
        pre_order(p->right);
    }
}

void in_order(node* p) {
    if (p != NULL) {
        in_order(p->left);
        printf("%c ", p->element);
        in_order(p->right);
    }
}

void post_order(node* p) {
    if (p != NULL) {
        post_order(p->left);
        post_order(p->right);
        printf("%c ", p->element);
    }
}

int main() {
    node* root = init_node('*');
    root->left = init_node('+');
    root->right = init_node('-');
    root->left->left = init_node('a');
    root->left->right = init_node('b');
    root->right->left = init_node('c');
    root->right->right = init_node('/');
    root->right->right->left = init_node('d');
    root->right->right->right = init_node('e');

    printf("TREE: [ ");
    pre_order(root);
    printf("]\n");

    printf("TREE: [ ");
    in_order(root);
    printf("]\n");

    printf("TREE: [ ");
    post_order(root);
    printf("]\n");

    clear(&root);

    printf("TREE: [ ");
    pre_order(root);
    printf("]\n");

    return 0;
}

// 実行結果
// TREE: [ * + a b - c / d e ]
// TREE: [ a + b * c - d / e ]
// TREE: [ a b + c d e / - * ]
// TREE: [ ]
