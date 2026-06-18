# Sample list of names
names = ['Alice', 'Bob', 'Charlie', 'David', 'Eve']

# Using map with a lambda function to get the length of each name
name_lengths = list(map(lambda x: len(x), names))

# Using map with a defined function to capitalize each name
def capitalize_name(name):
    return name.upper()

capitalized_names = list(map(capitalize_name, names))

# Print the results
print("Original names:", names)
print("Name lengths:", name_lengths)
print("Capitalized names:", capitalized_names)

# Try creating your own map function!
# Uncomment and modify the line below:
your_result = list(map(lambda x: capitalize_name, names))
print("Your result:", your_result)
