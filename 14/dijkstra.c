#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 1000000
#define MAX_SIZE 100

typedef struct {
    int prev;
    int min_weight;
    bool visited;
} node;

typedef struct {
    int size;
    int mat[MAX_SIZE][MAX_SIZE];
} adj_mat;

adj_mat graph;
node nodes[MAX_SIZE];

int dijkstra(int start, int goal) {
    nodes[start].min_weight = 0;
    while (true) {
        // 未訪問で最小重みの点を決定
        int min_weight = INF;
        int target;
        for (int i = 0; i < graph.size; ++i) {
            if (!nodes[i].visited && nodes[i].min_weight < min_weight) {
                target = i;
                min_weight = nodes[i].min_weight;
            }
        }
        assert(min_weight != INF);  // グラフが連結ではない

        // ゴールに到達したら終了
        if (target == goal) {
            return nodes[goal].min_weight;
        }

        // ターゲットを訪問し、そこから進める点の重みを更新
        nodes[target].visited = true;
        for (int neighbor = 0; neighbor < graph.size; ++neighbor) {
            int total_weight = nodes[target].min_weight + graph.mat[target][neighbor];
            if (total_weight < nodes[neighbor].min_weight) {
                nodes[neighbor].min_weight = total_weight;
                nodes[neighbor].prev = target;
            }
        }
    }
}

int main(void) {
    // グラフとノードを初期化
    for (int i = 0; i < MAX_SIZE; ++i) {
        nodes[i].min_weight = INF;
        nodes[i].visited = false;
        nodes[i].prev = -1;
        for (int j = 0; j < MAX_SIZE; ++j) {
            graph.mat[i][j] = INF;
        }
    }

    // 講義スライドと同じサンプルデータを入力
    graph.size = 6;
    graph.mat[0][1] = 6;
    graph.mat[0][2] = 4;
    graph.mat[1][3] = 3;
    graph.mat[2][4] = 3;
    graph.mat[2][5] = 6;
    graph.mat[4][1] = 2;
    graph.mat[4][3] = 1;
    int start = 0;
    int goal = 3;

    // 最短となる重みの総和を計算
    printf("Weight: %d\n", dijkstra(start, goal));

    // ゴールからスタートまでのルートを出力
    int route_node = goal;
    printf("Route: %d", route_node);
    while (true) {
        route_node = nodes[route_node].prev;
        printf(" <- %d", route_node);
        if (route_node == start)
            break;
    }
    printf("\n");
    return 0;
}

// 実行結果
// Weight: 8
// Route: 3 <- 4 <- 2 <- 0
