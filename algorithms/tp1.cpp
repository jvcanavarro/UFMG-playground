#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void dfs(const unordered_map<int, vector<int>>& graph, int v, vector<bool>& visited) {
    visited[v - 1] = true;
    cout << "v: " << v << endl;
    for (int w : graph.at(v)) {
        cout << "w: " << w << endl;
        if (!visited[w - 1]) {
            dfs(graph, w, visited);
        }
    }
}

bool is_connected(const unordered_map<int, vector<int>>& graph, int n_nodes) {
    for (int v = 1; v <= n_nodes; ++v) {
        vector<bool> visited(n_nodes, false);
        dfs(graph, v, visited);
        if (find(visited.begin(), visited.end(), false) != visited.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    int n_intersecs, n_streets;
    cin >> n_intersecs >> n_streets;

    while (n_intersecs != 0 && n_streets != 0) {
        vector<pair<int, int>> edges;
        unordered_map<int, vector<int>> graph;
        for (int i = 0; i < n_streets; ++i) {
            int v, w, p;
            cin >> v >> w >> p;

            edges.push_back({v, w});
            if (p == 2) {  // bidirectional
                edges.push_back({w, v});
            }

            graph[v].push_back(w);
            if (p == 2) {  // bidirectional
                graph[w].push_back(v);
            }
        }

        int n_nodes = graph.size();
        cout << (is_connected(graph, n_nodes) ? 1 : 0) << endl;

        cin >> n_intersecs >> n_streets;
    }

    return 0;
}