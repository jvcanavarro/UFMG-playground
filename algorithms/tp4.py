class Graph:
    def __init__(self, v):
        self.v = v
        self.adj = [[]] * self.v

    def get_connected_components(self):
        visited = [False] * self.v
        
        cc = 0
        for v in range(self.v):
            if visited[v] is False:
                self.dfs(v, visited)
                cc += 1
        return cc

    def dfs(self, v, visited):
        visited[v] = True
        for i in self.adj[v]:
            if not visited[i]:
                self.dfs(i, visited)

    def add_edge(self, v, w):
        self.adj[v].append(w)
        self.adj[w].append(v)


t = int(input())

for _ in range(t):
    n, m, b, e = map(int, input().split(" "))
    graph = Graph(n)
    for _ in range(m):
        x, y = map(int, input().split(" "))
        graph.add_edge(x - 1, y - 1)
        graph.add_edge(y - 1, x - 1)

    cc = graph.get_connected_components()

    minimum = 1e18
    for z in range(cc, n + 1):
        cost = (b * z) + (n - z) * e
        minimum = min(minimum, cost)

    print(minimum)
