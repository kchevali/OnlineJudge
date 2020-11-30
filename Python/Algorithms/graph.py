from collections import deque


"""
BFS: Unweighted - find path
find path from single source
Root - int, adj[][] - int,prev[]-int,depth[]-int"""


def bfs(root, adj, prev, depth, visited):
    q = deque()
    prev[root] = root
    q.append(prev[root])
    depth[root] = 1
    visited[root] = True
    while len(q) > 0:
        a = q.popleft()
        for b in adj[a]:
            if (not visited[b]):
                visited[b] = True
                depth[b] = depth[a] + 1
                prev[b] = a
                q.append(b)


def test_bfs():
    root = 0
    n = 4
    adj = [
        [2],
        [3],
        [1],
        []
    ]
    # 0 -> 2 -> 1 -> 3
    prev = [0 for _ in range(n)]
    depth = [100000000 for _ in range(n)]
    bfs(root, adj, prev, depth)
    print("Previous:", prev)
    print("Depth:", depth)


if __name__ == '__main__':
    test_bfs()
