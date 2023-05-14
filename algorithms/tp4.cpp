#include <iostream>
#include <vector>

class Graph {
private:
    int v;
    std::vector<std::vector<int>> adj;

public:
    Graph(int v) : v(v), adj(v) {}

    int get_connected_components() {
        std::vector<bool> visited(v, false);

        int cc = 0;
        for (int i = 0; i < v; ++i) {
            if (!visited[i]) {
                dfs(i, visited);
                cc++;
            }
        }
        return cc;
    }

    void dfs(int v, std::vector<bool>& visited) {
        visited[v] = true;
        for (int i : adj[v]) {
            if (!visited[i]) {
                dfs(i, visited);
            }
        }
    }

    void add_edge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
};

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int n, m, b, e;
        std::cin >> n >> m >> b >> e;

        Graph graph(n);

        for (int j = 0; j < m; ++j) {
            int x, y;
            std::cin >> x >> y;
            graph.add_edge(x - 1, y - 1);
            graph.add_edge(y - 1, x - 1);
        }

        int cc = graph.get_connected_components();
        long long minimum = 1e18;

        for (int z = cc; z <= n; ++z) {
            long long cost = static_cast<long long>(b) * z + static_cast<long long>(n - z) * e;
            minimum = std::min(minimum, cost);
        }

        std::cout << minimum << std::endl;
    }

    return 0;
}