import re


def main():

    # get Credit Card Number from user
    cc = input("Number: ")

    # run Checksum
    if checkSum(cc) == False:
        print("INVALID")
        return

    # AMEX starts with 34 or 37
    amex = "^3[47]"
    # MASTERCARD start with 51, 52, 53, 54, 55
    mastercard = "^5[1-5]"
    # VISA start with 4
    visa = "^4"

    # check starting digits of number and print card type
    if re.match(amex, cc):
        print("AMEX")
    elif re.match(mastercard, cc):
        print("MASTERCARD")
    elif re.match(visa, cc):
        print("VISA")
    else:
        print("INVALID")


# CREDIT CARD CHECKSUM
# multiply every other digit by 2, starting with the second to last digit, and add the products' digits together
# add the sum to the sum of the digits that weren't multiplied by 2
# if the totals' last digit is 0, the number is valid
def checkSum(cc):

    ccLen = len(cc)
    eoDigit = ''
    eoSum = 0
    ooSum = 0

    # iterate through every second number
    # starting from second to last
    for i in range(2, ccLen+1, 2):
        # multiply digit by 2
        x = int(cc[ccLen-i])*2
        # add all digits together
        eoDigit += str(x)

    # sum all digits of multiplied digits
    for i in range(len(eoDigit)):
        eoSum += int(eoDigit[i])

    # sum all other digits that were not multiplied
    for i in range(1, ccLen+1, 2):
        ooSum += int(cc[ccLen-i])

    # now sum all digits
    cSum = eoSum + ooSum

    # if last digit is 0
    if cSum % 10 == 0:
        # valid checksum
        return True
    else:
        # invalid checksum
        return False


main()