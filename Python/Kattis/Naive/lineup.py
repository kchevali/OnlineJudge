n = int(input())
for i in range(n):
    s = input()
    if i == 1:
        isInc = s > prev
    elif i > 1 and (s > prev) != isInc:
        isInc = None
    prev = s
if isInc != None:
    print("INCREASING" if isInc else "DECREASING")
else:
    print("NEITHER")
