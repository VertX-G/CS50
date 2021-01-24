import re
from cs50 import get_string


# get_string for user input
text = get_string("Text: ")

letters = "[a-zA-Z]"    # any a to z or A to Z characters
letterCount = len(re.findall(letters, text))
words = "\S+"   # any collection of 1 or more non-whitespace characters
wordCount = len(re.findall(words, text))
sentences = "[\.\!\?]"  # any occurence of a ".", "!", or "?" marks the end of a sentence
sentenceCount = len(re.findall(sentences, text))

L = (100/wordCount)*letterCount     # L = average number of letters per 100 words
S = (100/wordCount)*sentenceCount   # S = average number of sentences per 100 words

# Coleman-Liau index = (0.0588 * L - 0.296 * S - 15.8)
f = round(0.0588 * L - 0.296 * S - 15.8)

# program should print "Grade X" where X is the grade level computed by Coleman_Liau formula, rounded to nearest integer.
# if index number is >=16, output "Grade 16+"
# is index number is <1, output "Before Grade 1"
if f < 1:
    print(f"Before Grade 1")
elif f >= 16:
    print(f"Grade 16+")
else:
    print(f"Grade {f}")