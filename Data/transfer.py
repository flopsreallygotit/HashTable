# This program breaks the text down into words and places each word on new line.
# Use it on big texts.

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def deletePunctuation(word):
    return ''.join([char if char.isalnum() else '' for char in word])

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inputFilename = "test.txt"

filenameParts = inputFilename.split('.')
filenameParts.insert(1, "Words.")

outputFilename = ''.join(filenameParts)

inputFile  = open(inputFilename)
outputFile = open(outputFilename, 'w')

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

words = set()

for line in inputFile.readlines():
    for word in line.split():
        words.add(deletePunctuation(word) + '\n')

outputFile.writelines(words)

outputFile.close()
inputFile.close()

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
