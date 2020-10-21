from random import randint

width = 5
height = 5
print(width, height)
for i in range(width):
    for j in range(height):
        print(randint(0, 4), end="")
    print()
