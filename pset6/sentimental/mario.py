# mario.py

#prompt the user & validate the number

while True:
    try:
        height = int(input("Height of the pyramid: "))
    except ValueError:
        print("Please enter a number!")

    if height > 0:
        break
i = 0
for x in range(height):
    for y in (range(height- i - 1)):
        print(" ",end="")

    for z in (range(i +1 )):
        print("#",end="")
    print(" ",end="")
    print(" ",end="")
    for a in range(i + 1):
        print("#",end="")
    print(" ")
    i += 1
