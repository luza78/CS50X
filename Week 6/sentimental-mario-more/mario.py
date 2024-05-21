


n = input("Input a height: ")

n = int(n)
i = 0
k = n - 1
j = 0
l = 0

while i < n:
    i += 1
    while k > i:
        print(" ", end="")
        k -= 1
    while j <= i:
        print("#", end="")
        j += 1
        if j == i:
            print(" ", end="")
            j += 1
    while l <= i:
        print("#", end="")
        l += 1
    print("")


