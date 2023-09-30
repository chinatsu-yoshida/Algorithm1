#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_GRAPH_SIZE 100

typedef struct {
    bool M[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
} adjacency_matrix;

typedef struct edge_cell_ {
    int destination;
    struct edge_cell_* next;
} edge_cell;

typedef struct {
    edge_cell* cells[MAX_GRAPH_SIZE];
} adjacency_list;

edge_cell* init_edge_cell(int dest) {
    edge_cell* c = (edge_cell*)malloc(sizeof(edge_cell));
    c->destination = dest;
    c->next = NULL;
    return c;
}

void visit_mat(adjacency_matrix* mat, bool* visited, int v) {
    visited[v] = true;
    for (int z = 0; z < MAX_GRAPH_SIZE; ++z) {
        if (mat->M[v][z] && !visited[z]) {
            printf("%d -> %d\n", v, z);
            visit_mat(mat, visited, z);
        }
    }
}

void dfs_mat(adjacency_matrix* mat) {
    printf("dfs in matrix:\n");
    bool visited[MAX_GRAPH_SIZE] = {0};
    for (int i = 0; i < MAX_GRAPH_SIZE; ++i) {
        if (!visited[i]) {
            visit_mat(mat, visited, i);
        }
    }
}

void visit_list(adjacency_list* list, bool* visited, int v) {
    visited[v] = true;
    edge_cell* p = list->cells[v];
    while (p) {
        int z = p->destination;
        if (!visited[z]) {
            printf("%d -> %d\n", v, z);
            visit_list(list, visited, z);
        }
        p = p->next;
    }
}

void dfs_list(adjacency_list* list) {
    printf("dfs in list:\n");
    bool visited[MAX_GRAPH_SIZE] = {0};
    for (int i = 0; i < MAX_GRAPH_SIZE; ++i) {
        if (!visited[i]) {
            visit_list(list, visited, i);
        }
    }
}

int main() {
    adjacency_matrix mat = {0};
    mat.M[0][1] = true;
    mat.M[0][2] = true;
    mat.M[0][3] = true;
    mat.M[1][0] = true;
    mat.M[1][3] = true;
    mat.M[2][0] = true;
    mat.M[2][4] = true;
    mat.M[2][5] = true;
    mat.M[3][0] = true;
    mat.M[3][1] = true;
    mat.M[3][5] = true;
    mat.M[4][2] = true;
    mat.M[4][5] = true;
    mat.M[4][6] = true;
    mat.M[5][2] = true;
    mat.M[5][3] = true;
    mat.M[5][4] = true;
    mat.M[6][4] = true;
    dfs_mat(&mat);
    printf("\n");

    // ここでのnextはリスト表現における次なので、
    // グラフとしての次ではないことに注意してください。
    adjacency_list l = {0};
    l.cells[0] = init_edge_cell(1);
    l.cells[0]->next = init_edge_cell(2);
    l.cells[0]->next->next = init_edge_cell(3);
    l.cells[1] = init_edge_cell(0);
    l.cells[1]->next = init_edge_cell(3);
    l.cells[2] = init_edge_cell(0);
    l.cells[2]->next = init_edge_cell(4);
    l.cells[2]->next->next = init_edge_cell(5);
    l.cells[3] = init_edge_cell(0);
    l.cells[3]->next = init_edge_cell(1);
    l.cells[3]->next->next = init_edge_cell(5);
    l.cells[4] = init_edge_cell(2);
    l.cells[4]->next = init_edge_cell(5);
    l.cells[4]->next->next = init_edge_cell(6);
    l.cells[5] = init_edge_cell(2);
    l.cells[5]->next = init_edge_cell(3);
    l.cells[5]->next->next = init_edge_cell(4);
    l.cells[6] = init_edge_cell(4);
    dfs_list(&l);
    printf("\n");

    return 0;
}

// 実行結果
// dfs in matrix:
// 0 -> 1
// 1 -> 3
// 3 -> 5
// 5 -> 2
// 2 -> 4
// 4 -> 6
//
// dfs in list:
// 0 -> 1
// 1 -> 3
// 3 -> 5
// 5 -> 2
// 2 -> 4
// 4 -> 6
