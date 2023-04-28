def deletePunctuation(word):
    return "".join([char if char.isalnum() else '' for char in word])

inputFile  = open("data.txt")
outputFile = open("fightClubWords.txt", "w")

words = set()

for line in inputFile.readlines():
    for word in line.split():
        words.add(deletePunctuation(word) + '\n')

outputFile.writelines(words)

outputFile.close()
inputFile.close()
