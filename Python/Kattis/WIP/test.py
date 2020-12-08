n = 500
with open("WIP/test.txt", "w") as f:
    out = "1" * n
    out += "\n"
    out *= n
    f.write(str(n) + " " + str(n) + "\n")
    f.write(out)
