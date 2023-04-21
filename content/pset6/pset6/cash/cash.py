# no library
# error treatment

while True:
    try:
        change = float(input("Troco: "))
        if change > 0:    # verificando se o input é positivo
            break
    except:
        change = None
# counting coins
# optmizing with math
coins = 0
change = round(change * 100)
if change >= 25:
    coins += change // 25
    change = change % 25

if change >= 10:
    coins += change // 10
    change = change % 10

if change >= 5:
    coins += change // 5
    change = change % 5

if change >= 1:
    coins += change

print(coins)

