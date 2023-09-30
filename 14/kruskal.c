#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 1000000
#define MAX_SIZE 100

typedef struct {
    int from;
    int into;
    int weight;
} edge;

void swap(edge* a, edge* b) {
    edge tmp = *a;
    *a = *b;
    *b = tmp;
}

// DisjointSet: 素集合を表すデータ構造
//   メンバー変数:
//     int parents[MAX_SIZE];
//   メンバー関数:
//     init_parents();
//     find_root(int x);
//     unite(int x, int y);
int parents[MAX_SIZE];

void init_parents() {
    // 最初は全てをルートとしてDisjointSetを初期化
    for (int i = 0; i < MAX_SIZE; ++i) {
        parents[i] = i;
    }
}

int find_root(int x) {
    if (parents[x] == x) {
        return x;
    }
    return parents[x] = find_root(parents[x]);  // path compression
}

void unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {  // xとyのルートが元々同じなら何もしない
        return;
    }
    parents[x] = y;
}

void down_heap(edge* edges, int target, int end) {
    while (true) {
        int comparing = 2 * target + 1;
        if (comparing > end) {
            break;
        }
        if (comparing != end &&
            edges[comparing + 1].weight < edges[comparing].weight) {
            comparing++;
        }
        if (edges[target].weight < edges[comparing].weight) {
            break;
        }
        swap(&edges[target], &edges[comparing]);
        target = comparing;
    }
}

void kruskal(edge* edges, int num_edges) {
    init_parents();
    for (int i = num_edges / 2 - 1; i >= 0; --i) {
        down_heap(edges, i, num_edges - 1);
    }

    int total_weight = 0;
    for (int i = num_edges - 1; i >= 0; --i) {
        edge e = edges[0];
        // エッジが異なる集合を結んでいる場合
        if (find_root(e.from) != find_root(e.into)) {
            printf("%d-%d: %d\n", e.from, e.into, e.weight);
            total_weight += e.weight;  // 最小全域木の重みに加算
            unite(e.from, e.into);     // 集合を結合
        }
        if (i > 0) {
            swap(&edges[0], &edges[i]);  // ヒープの先頭を更新
            down_heap(edges, 0, i);      // ヒープを更新
        }
    }
    printf("Total weight: %d\n", total_weight);
}

int main() {
    edge edges[8] = {{0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {2, 3, 3}, {2, 5, 2}, {2, 4, 4}, {3, 4, 3}, {4, 5, 3}};
    kruskal(edges, 8);
}

// 実行結果
// 2-5: 2
// 1-2: 2
// 4-5: 3
// 2-3: 3
// 0-1: 4
// Total weight: 14
