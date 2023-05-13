#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 100000

void dfs(int **graph, int n_nodes, int v, bool *visited) {
    visited[v - 1] = true;
    for (int w = 1; w <= n_nodes; w++) {
        if (graph[v][w] && !visited[w - 1]) {
            dfs(graph, n_nodes, w, visited);
        }
    }
}

bool is_connected(int **graph, int n_nodes) {
    for (int v = 1; v <= n_nodes; v++) {
        bool visited[MAX_N];
        memset(visited, false, sizeof(visited));
        dfs(graph, n_nodes, v, visited);
        if (memchr(visited, false, n_nodes * sizeof(bool)) != NULL) {
            return false;
        }
    }
    return true;
}

int main() {
    int n_intersecs, n_streets;
    scanf("%d %d", &n_intersecs, &n_streets);

    while (n_intersecs != 0 && n_streets != 0) {
        // define if connectedness is satisfied using DFS traversal
        int **graph = malloc(sizeof(int *) * (n_intersecs + 1));
        for (int i = 1; i <= n_intersecs; i++) {
            graph[i] = calloc(n_intersecs + 1, sizeof(int));
        }

        for (int i = 0; i < n_streets; i++) {
            int v, w, p;
            scanf("%d %d %d", &v, &w, &p);
            graph[v][w] = 1;
            if (p == 2) { // bidirectional 
                graph[w][v] = 1;
            }
        }

        printf("%d\n", (is_connected(graph, n_intersecs) ? 1 : 0));

        for (int i = 1; i <= n_intersecs; i++) {
            free(graph[i]);
        }
        free(graph);

        scanf("%d %d", &n_intersecs, &n_streets);
    }

    return 0;
}