

def longest_increasing_subsequence(a, n):
    counter = 0
    lis = []

    parent = []

    # initialize lis with 1 as each element
    # has a subsequence length equal to 1
    for i in range(n):
        lis.append(1)
    # initialize parent with -1
    for i in range(n):
        parent.append(-1)

    for i in range(n):
        for j in range(i):

            if a[j] < a[i]:
                if lis[i] < lis[j] + 1:
                    lis[i] = lis[j] + 1
                    parent[i] = j

    length = 0
    pos = 0

    # length of subsequence is the maximum value
    # in lis array
    for i in range(n):
        if length < lis[i]:
            length = lis[i]
            pos = i

    return length


# Driver code
a = [ord(i) for i in input()]

n = len(a)

# function calling
print(26 - longest_increasing_subsequence(a, n))
