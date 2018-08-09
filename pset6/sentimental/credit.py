#i = True
while  True:
    try:
        card_number = int(input("Card Number: "))
        if (0 < card_number <9999999999999999):
            break
    except ValueError:
        continue

digit = len(str(card_number))
t_digit = int(digit) - 1
temp_card = str(card_number)
sum_digit = 0
sum_other_digit = 0

for i in range(digit):
    if i % 2 == 0:
        last = temp_card[t_digit]
        last = int(last)
        sum_digit += last
    elif i % 2 != 0:
        last = temp_card[t_digit]
        last = int(last)
        other_by_2 = last * 2
        if (other_by_2 > 9):
            other = str(other_by_2)
            total_other = int(other[0]) + int(other[1])
            sum_other_digit += total_other
        else:
            sum_other_digit += other_by_2
    t_digit -= 1

total_sum = sum_digit + sum_other_digit
company_id = int(temp_card[0:2])

if (total_sum % 10 == 0):
    if digit == 15 and (company_id == 34 or company_id == 37):
        print("AMEX")
    elif (digit == 16 and (company_id == 51  or company_id == 52 or company_id == 53)):
        print("MASTERCARD")
    elif ((digit == 13 or digit == 16) and( company_id[0] == 4)):
        print("VISA")
    else:
        print("INVALID")