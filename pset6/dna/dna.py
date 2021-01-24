# user to input as the first command-line argument, the name of a CSV file containing the STR counts for a list of individuals
# and as the second command-line argument, the name of a text file containing the DNA sequence to identify
# print error if executed with incorrect number of file names

# open CSV file and write content's to memory
# first row will be column names
# first column with be the word 'name' and remaining columns will be STR sequences

# open text file and read dna sequence to memory

# for each of the STR's in the CSV file, the program should compute the longest run of consecutive repeats of the DNA sequence to identify
# if the str counts match exactly with any of the individuals in the CSV file, program should print individual's name
# else print "No match" if there are no matches.