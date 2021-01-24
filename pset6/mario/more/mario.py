from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        # check input
        if height >= 1 and height <= 8:
            break
    # generate pyramid
    generate(height, height)


def generate(layer, height):

    i = layer

    # base case
    if i == 0:
        return

    # generate pyramid for current layer
    generate(i-1, height)
    print(" "*(height-i) + "#"*i + " "*2 + "#"*i)


main()

'''
Alt option:

There's one way to handle this without two inputs to the recursive function,
but that would require you to not print inside the recursive function,
but return something (like a string, or maybe better a list of strings),
and print in the main function.
That way you could take the result of the previous iteration,
and add something to each line, and add another line.
Can't do that if the line is already on the terminal.
'''