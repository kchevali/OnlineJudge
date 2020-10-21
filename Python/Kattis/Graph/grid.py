from collections import deque
from math import inf
# from time import time

# gen = 0


def bfs(root, adj, depth):
    # global gen
    q = deque()
    q.append(root)
    depth[root] = 0

    visited = [False for _ in range(n)]
    visited[root] = True

    while len(q) > 0:
        a = q.popleft()  # pop() - wouldn't work - TLE
        for b in adj[a]:
            if (not visited[b]):
                depth[b] = depth[a] + 1
                visited[b] = True
                # gen += 1
                q.append(b)


cols, rows = tuple(map(int, input().split(" ")))
n = cols * rows
# print("N:", n)

arr = [input() for _ in range(cols)]
adj = [[] for _ in range(n)]

for i in range(cols):  # horizontal
    for j in range(rows):  # vertical

        hops = int(arr[i][j])  # num of hops
        if hops > 0:
            index = i * rows + j

            if i >= hops:
                adj[index].append((i - hops) * rows + j)  # left

            if i < cols - hops:
                adj[index].append((i + hops) * rows + j)  # right

            if j >= hops:
                adj[index].append(i * rows + j - hops)  # up
            if j < rows - hops:
                adj[index].append(i * rows + j + hops)  # down

root = 0
depth = [inf for _ in range(n)]
# start = time()
bfs(root, adj, depth)
print(depth[-1] if depth[-1] < inf else -1)


# print("Total Gen:", gen)
# print("Time Taken:", time() - start)
