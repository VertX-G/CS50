x = int(input("X: "))
y = int(input("Y: "))
count = int(input("Count: "))

for i in range(1, count+1):
    p = ""
    if i % x == 0:
        p += "fizz"
    if i % y == 0:
        p += "buzz"
    if p == "":
        p += str(i)
    print(p)