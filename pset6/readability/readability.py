from cs50 import get_string


# ord(c) - input a unicode character as a string, and returns it's integer
# chr(i) - input unicode integer, and returns string character

# Coleman-Liau index = (0.0588 * L - 0.296 * S - 15.8)
# L = average number of letters per 100 words
# S = average number of sentences per 100 words

# get_string for user input

# count number of letters, words and sentences in the text
# letter =  any a to z or A to Z
# words = any sequence of characters separated by spaces
# sentence = any occurence of a ".", "!", or "?" marks the end of a sentence

# program should print "Grade X" where X is the grade level computed by Coleman_Liau formula, rounded to nearest integer.
# if index number is >=16, output "Grade 16+"
# is index number is <1, output "Before Grade 1"