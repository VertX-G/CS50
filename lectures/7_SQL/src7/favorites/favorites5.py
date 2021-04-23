# Prints popularity of titles in CSV, sorted by popularity

import csv

# For accumulating (and later sorting) titles
titles = {}

# Open CSV file
with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file, adding each (uppercased) title to dictionary
    for row in reader:

        # Canoncalize title
        title = row["title"].strip().upper()

        # Count title
        if title in titles:
            titles[title] += 1
        else:
            titles[title] = 1

# Function for comparing titles by popularity
def f(title):
    return titles[title]

# Print titles in sorted order
for title in sorted(titles, key=f, reverse=True):
    print(title, titles[title])
