#

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

text = """Interesting facts about the Moon. The Moon is Earth's only satelite. There are
several interesting facts about the Moon and how it affects life here on Earth. On average, the
Moon moves 4cm away from the Earth every year. This yearly drift is mot significant enough to
cause immediate effects on Earth. The highest daylight temperature of the Moon is 127 C."""

sentences = text.split('. ')
print (sentences)

for sentence in sentences:
    if 'temperature' in sentence:
        print(sentence)