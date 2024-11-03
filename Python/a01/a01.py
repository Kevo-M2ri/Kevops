# **----------------------------------------------------------------------------
# Author:      Kelvin Muturi
# Date:        October 6, 2024
# Assignment:  CS-161A Assignment a01
# Description: This program calculates the amount of Pizza required for a pizza
#              party and the total cost of the required pizza
# Inputs:      number of people as an integer
# Outputs:     number of Pizzas as an integer and their total cost as a double
#  -----------------------------------------------------------------------****/

numPeople = int()
pizzas = int()
slicesPerPizza = int(12)
slicesPerPerson = int(2)
price = float(14.95)
cost = float()

print("Welcome to my pizza party Calculator!")

print("Enter the number of people attending: ")
input(numPeople)

pizzas = numPeople * slicesPerPerson / slicesPerPizza
cost = price * pizzas

print("You will need: ", pizzas)
print("The total cost is: $", cost)

print("Thank you!! Goodbye!")