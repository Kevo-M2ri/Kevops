from datetime import date

print(date.today())

parsecs_input = input("Input number of parsecs: ")
parsecs = int(parsecs_input)
lightyears = 3.26156 * parsecs

print(parsecs_input + " parsecs is " + str(lightyears) + " lightyears")

object_size = 10
if object_size > 5:
    print('We need to keep an eye on this object')
else:
    print('Object poses no threat.')