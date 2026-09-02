def greatest(num1, num2, num3):
    if num1 > num2 > num3:
        return num1
    elif num2 > num1 > num3:
        return num2
    elif num3 > num1 > num2:
        return num3
    else:
        if num1 == num2 > num3 or num2 == num3 > num1 or num1 == num3 > num2:
            return "Its a tie!"
print(greatest(5, 5, 2))
print(greatest(2, 7, 5))
 
# Write your max_num function here:
