from math import ceil
n = int(input())
for i in range(n):
    s = input()
    for j in range(len(s)):
        s2 = s[:j + 1] * ceil(len(s) / (j + 1))
        if (len(s2) > len(s)):
            s2 = s2[:len(s)]
        if s2 == s:
            print(j + 1)
            break
