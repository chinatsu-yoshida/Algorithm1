#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

// C 言語では、struct name {}; と定義してしまうと変数宣言の
// 際に毎回 struct name var; と書く必要があります。
// typedef struct {} name; と書くことで name var; と簡潔に
// 書くことができます。
typedef struct {
    int length;
    int elements[SIZE];
} sequence;

// 2 つの理由から関数には構造体のポインタを渡しています。
// 1. 関数内で構造体を変更するため。
//    構造体自体を渡してしまうと、構造体のコピーが発生するため
//    関数呼び出し側が渡したインスタンスに影響を与えられません。
// 2. パフォーマンスを改善するため。
//    構造体自体を渡してしまうと、構造体のコピーが発生するため
//    低速です。CPU の演算速度に比べるとメモリアクセスは超低速です
//    ので注意が必要です。ポインタを渡すと構造体のコピーが発生せず
//    ポインタのコピーが発生します。
//    sequence のサイズは sizeof(int) * (1 + SIZE) ですので
//    大抵の処理系では 4004 bytes です。それに対してポインタは
//    8 bytes と圧倒的に小さいです。
void insert(sequence* seq, int pos, int val) {
    // 講義スライドにおける error の扱いは
    // 大きく分けて2種類の考え方ができます。
    // 1. assert で異常終了する。
    // 2. 何もせず return する。
    // どちらを採用するかについてはエラーの内容によります。
    // 大雑把には 1 番はプログラムのバグであり実行時に起きては
    // いけないものとみなす場合、2 番は起こってもよいものと
    // みなす場合に採用します。
    // ただし 2 番については、返り値が void でない場合は
    // 返り値の型に応じたエラー値を決める必要があり、関数を
    // 呼び出した側ではエラーチェックが必要となります。
    // 他の言語では exception を採用する場合もあります。
    assert(seq->length < SIZE);

    for (int i = seq->length - 1; i >= pos; i--) {
        seq->elements[i + 1] = seq->elements[i];
    }
    seq->length++;
    seq->elements[pos] = val;
}

// delete は C++ の予約語なので、念のため erase と書きます
void erase(sequence* seq, int pos) {
    seq->length--;
    for (int i = pos; i < seq->length; i++) {
        seq->elements[i] = seq->elements[i + 1];
    }
}

void print(sequence* seq) {
    printf("ELEMENTS: [ ");
    for (int i = 0; i < seq->length; i++) {
        printf("%d ", seq->elements[i]);
    }
    printf("]\n");
    printf("LENGTH  : %d\n", seq->length);
}

int main() {
    // list と異なり、固定長配列である array は
    // 大抵は動的確保(malloc)する必要がありません。
    sequence seq = {0, {0}};
    for (int i = 0; i < 10; i++) {
        insert(&seq, i, i);
    }
    print(&seq);

    erase(&seq, 5);
    print(&seq);

    return 0;
}

// 実行結果
// ELEMENTS: [ 0 1 2 3 4 5 6 7 8 9 ]
// LENGTH  : 10
// ELEMENTS: [ 0 1 2 3 4 6 7 8 9 ]
// LENGTH  : 9
