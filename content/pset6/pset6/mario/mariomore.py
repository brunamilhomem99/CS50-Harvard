from cs50 import get_int

while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# building pyramid
for i in range(1, height + 1):
    print(' ' * (height - i) + '#' * i + ' ' + '#' * i)