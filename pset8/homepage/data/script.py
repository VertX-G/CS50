import re
import csv

with open('quotes.txt', 'r') as f:
    src = f.read()

quoteCheck = '(?<=<p>\s)[\s\S]*?(?=\s</p>)'
authCheck = '(?<=>)[^<]*?(?=</a></p>)'
refCheck = '(?<=<p><a href=)[\s\S]*?(?=>)'

quotes = re.findall(quoteCheck, src)
authors = re.findall(authCheck, src)
references = re.findall(refCheck, src)

with open('quotes.csv', 'a') as csvFile:
    writer = csv.writer(csvFile)
    for i in range(len(quotes)):
        writer.writerow([quotes[i],authors[i],references[i]])