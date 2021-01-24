import re
from cs50 import get_string
from cs50 import get_int


cc = input("Number: ")
print(cc)
print()

# CREDIT CARD HASH ALGORITHM
# multiply every other digit by 2, starting with the second to last digit, and add the products' digits together
# add the sum to the sum of the digits that weren't multiplied by 2
# if the totals' last digit is 0, the number is valid

ccLen = len(cc)
eoDigit = ''
eoSum = 0
ooSum = 0

for i in range(2, ccLen+1, 2):
    print(f"{cc[ccLen-i]}")
    x = int(cc[ccLen-i])*2
    eoDigit += str(x)
print()

for i in range(len(eoDigit)):
    print(eoDigit[i])
    eoSum += int(eoDigit[i])
print()

for i in range(1, ccLen+1, 2):
    print(f"{cc[ccLen-i]}")
    ooSum += int(cc[ccLen-i])
print()

checkSum = eoSum + ooSum
print(checkSum)

if checkSum % 10 == 0:
    print("VALID")
else:
    print("INVALID")
     
print(eoSum)

# last line of output to be:

# AMEX
# Start with 34 or 37
# AMEX\n

# MASTERCARD
# Start with 51, 52, 53, 54, 55
# MASTERCARD\n

# VISA
# Start with 4
# VISA\n

# INVALID\n