from math import gcd
a, b, s = tuple(map(int, input().split()))

a, b = (min(a, b), max(a, b))

x = a
while x <= s:
    if(x % b == 0):
        print("yes")
        exit(0)
    x += a
print("no")
