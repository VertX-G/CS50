import re
import csv
import sys


def main():
    
    # check user iputs correct number of command-line arguments
    if len(sys.argv) != 3:
        # if not, return error and exit
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    
    # variables for file names
    csvFileName = sys.argv[1]
    seqFileName = sys.argv[2]
    
    # variables for DNA sequence
    dnaSequence = ""
    
    # list of all people
    people = []
    
    # read DNA sequence from file to string
    with open(seqFileName, "r") as file:
        dnaSequence = file.read()
    
    # read CSV people into list of dictionaries
    with open(csvFileName, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            people.append(row)
    
    # create an empty dictionary to hold the STR data for the test dna string
    dna = dict.fromkeys(people[0])
    
    # for each key in the list
    # find the longest sequential string of that key in the DNA sequence
    # and save that to the dna dictionary
    for key in dna.keys():
        # check all keys except 'name'
        if key != 'name':
            dna[key] = test_STR(key, dnaSequence)
    
    # find match for DNA dictionary in people dictionaries
    print(match(people, dna))


# find longest STR in dna sequence
def test_STR(strSequence, dnaSequence):

    # set up regex query, looking for the STR sequence
    testSTR = "((?:"+strSequence+")+)"

    # run regex query
    x = re.findall(testSTR, dnaSequence)
    # if query returns no hits (i.e. x is an empty list)
    if not x:
        return 0
    else:
        # return the number of repetitions for the longest STR sequence as a string
        return str(round(len(max(x))/len(strSequence)))


# find a match for the STR sequences in the list of people
def match(people, dna):
    for person in people:
        # set the name of the donor dna dictionary equal to the dictionary we are currently testing for easy comparison
        dna['name'] = person['name']
        # if the dna dictionary has a comparison in the list of people
        if dna == person:
            # return the name of that person
            return dna['name']
    # if no name was returned, return 'no match'
    return 'no match'


main()