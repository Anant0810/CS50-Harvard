
while True:

    try:
        money = int(input("How much we owe you: "))
        money = money
        break
    except ValueError:
        print("Please give a integer!")
#counting how many coins
count = 0
# money

quater = 25
cent = 1
dime = 10
nikel = 5
dollar = 100

#Coins = {quater: 25.0, cent: 1.0, dime: 10.0, dollar: 100.0, nikel : 5.0}
#print(Coins[dollar])

while money >= dollar:
    money = money - dollar
    count += 1
while money >= quater:
    money = money - quater
    count += 1
while money >= dime:
    money = money - dime
    count += 1
while money >= nikel:
    money = money - nikel
    count += 1
while money >= cent:
    count += 1
    money = money - cent


print(count)



