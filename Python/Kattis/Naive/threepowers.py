x = 1
threes = [0]*64
for i in range(64):
    threes[i] = str(x)
    x *= 3

n = int(input()) - 1
while n != -1:
    i = 0
    out = []
    while n != 0:
        if((n & 1) != 0):
            out.append(threes[i])
        i += 1
        n >>= 1
    print("{ " + ", ".join(out) + " }")
    n = int(input()) - 1
