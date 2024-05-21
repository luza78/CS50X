
def main():

    height = get_height()

    print_grid(height)


def get_height():
    while True:
        height = input("Input height: ")
        if height.isdigit():
            height = int(height)
            if height > 0 and height < 9:
                return height


def print_grid(height):
    k = 0
    for i in range(0, height, 1):
        n = 1
        l = height
        k += 1
        while k < l:
            l -= 1
            print(" ", end="")

        while n <= k:
            n += 1
            print("#", end="")

        print("")


main()
