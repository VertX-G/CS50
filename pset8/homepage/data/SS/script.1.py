import re

with open('quotes.txt', 'r') as f:
    src = f.read()

quoteCheck = '(?<=<p>\s)[\s\S]*?(?=\s</p>)'
authCheck = '(?<=>)[^<]*?(?=</a></p>)'
refCheck = '(?<=<p><a href=)[\s\S]*?(?=>)'

quotes = re.findall(quoteCheck, src)
authors = re.findall(authCheck, src)
references = re.findall(refCheck, src)

with open('parsedquotes.txt', 'w') as file:
    for i in range(len(quotes)):
        file.write('{\n\t"text": "'+quotes[i]+'",\n\t"author": "'+authors[i]+'",\n\t"ref": "'+references[i]+'"\n},\n')
