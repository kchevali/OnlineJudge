n = int(input())
for _ in range(n):
    i, n = tuple(map(int, input().split()))
    print(i, (int)(n * (n + 1) / 2), (n * n), (n * (n + 1)))
