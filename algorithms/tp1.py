from collections import defaultdict


def dfs(graph, v, visited):
    visited[v - 1] = True
    print("v:", v)
    # print("graph:", graph)
    # print("graph[v]:", graph[v])
    # print("graph.keys()", graph.keys())
    if v in graph.keys():
        for w in graph[v]:
            print("w:", w)
            if not visited[w - 1]:
                dfs(graph, w, visited)


def is_connected(graph, n_nodes):
    print("graph:", graph)
    for v in range(1, n_nodes + 1):
        visited = [False] * n_nodes

        dfs(graph, v, visited)

        if False in visited:
            return False
    
    return True


n_intersecs, n_streets = map(int, input().split(" "))

# iterate through test cases until input is '0, 0'
while n_intersecs != 0 and n_streets != 0:

    # define if connectedness is satisfied using DFS traversal to 
    edges = []
    nodes = set()
    for _ in range(n_streets):
        v, w, p = map(int, input().split(" "))
        
        edges.append((v, w))
        if p == 2: #bidirectional 
            edges.append((w, v))

        nodes.update([v, w])


    graph = defaultdict(lambda: set())
    for src, dest in edges:
        graph[src].add(dest)

    n_nodes = len(nodes)
    print(1 if is_connected(graph, n_nodes) else 0)

    n_intersecs, n_streets = map(int, input().split(" "))
