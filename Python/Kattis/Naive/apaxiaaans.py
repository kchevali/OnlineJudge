s = input()
size = 0
while size != len(s):
    size = len(s)
    for i in range(26):
        letter = chr(ord("a") + i)
        s = s.replace(letter * 2, letter)
print(s)
