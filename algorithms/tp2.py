def shortest_path(a, b):
    if a == b: 
        return 0
    queue = [a]
    visited = {a}
    distance = 0
    while queue:
        for _ in range(len(queue)):
            node = queue.pop(0)
            neighbors = [node + 1, int(str(node)[::-1])]
            filtered = filter(lambda x:x not in visited and x < 10000, neighbors)
            for neighbor in filtered:
                if neighbor == b: # a == b
                    return distance + 1
                visited.add(neighbor)
                queue.append(neighbor)
        distance += 1

n_tests = int(input())
for _ in range(n_tests):
    a, b = map(int, input().split(" "))
    print(shortest_path(a, b))
