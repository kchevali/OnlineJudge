from collections import deque

maxTime = 3610


def bfs(root, adj, depth, visited, target):
    depth[root] = 0
    if target == 0:
        return 0
    q = deque()
    q.append(root)

    visited[root] = True
    best_time = maxTime
    while len(q) > 0:
        a = q.popleft()  # current time
        for b in adj:  # iterate buttons times
            new_time = max(min(a + b, 3600), 0)  # bounds: 0,3600
            if (not visited[new_time]):
                visited[new_time] = True
                depth[new_time] = depth[a] + 1
                if new_time == target:
                    return target
                if new_time > target:
                    best_time = min(new_time, best_time)

                q.append(new_time)
    return best_time


test_cases = int(input())
for tc in range(test_cases):
    n, t = tuple(map(int, input().split()))  # num of buttons, target time
    buttons = [int(time) for time in input().split() if time != "0"]
    root = 0
    # adj is buttons - 1D instead 2D array
    depth = [0 for _ in range(maxTime)]
    visited = [False for _ in range(maxTime)]

    best_time = bfs(root, buttons, depth, visited, t)
    print(depth[best_time], best_time - t)
