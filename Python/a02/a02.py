import math

<<<<<<< HEAD
ficaDeduct = 0.0765
=======
FICADEDUCT = 0.0765

print("Welcome to my Salary Calculator!")

empIDNum = input("Enter employee ID number: ")
numHrsWorked = input("Enter the number of hours worked: ")
hourlyRate = input("Enter the hourly rate: $")
fedWholdRate = input("Enter the federal Tax withhold rate (enter percentage as decimal, for example: 17% = 0.17): ")

grossPay = numHrsWorked * hourlyRate
ficaDedux = FICADEDUCT * grossPay
fedTaxWhold = fedWholdRate * grossPay
totalDedux = ficaDedux + fedTaxWhold
netPay = grossPay - totalDedux

print(f"""Your payroll summary:
--------------------------------
    Gross amount paid is: ${round(grossPay, 2)} #fixme
    FICA deduction is: ${round(ficaDedux, 2)}
    Federal Tax Withholding is: ${round(fedTaxWhold, 2)}
    Total deductions: ${round(totalDedux, 2)}
    Net pay is: ${round(netPay, 2)}""")

<<<<<<< HEAD
print("Thank you. Goodbye!")
=======
print("Thank you. Goodbye!")
>>>>>>> 5d872f1f9201a04ff2d6d9cfbbba359e20a975c6
>>>>>>> 2016e0fa201ea531748fd222a697c734fdaf5c44
