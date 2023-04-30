import numpy as np
import matplotlib.pyplot as plt

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def parseHashTableStats (filename):
    file = open(filename)

    funcStats = [list(funcStat.split('\n')) for funcStat in file.read().split("\n\n")]
    funcStats.pop(-1) # funcStats[-1] = ['']

    indexes = []
    sizes   = []

    for funcStatIndex in range(len(funcStats)):
        currentIndexes = []
        currentSizes   = []
        for line in funcStats[funcStatIndex]:
            currentIndex, currentSize = map(int, line.split('\t'))

            currentIndexes.append(currentIndex)
            currentSizes.append(currentSize)

        indexes.append(currentIndexes)
        sizes.append(currentSizes)

    file.close()

    return indexes, sizes

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def visualizeStats (indexes, sizes, title):
    indexes = np.array(indexes)
    sizes   = np.array(sizes)

    plt.bar(indexes, sizes,
            color = "purple",
            label = "$D$ = " + str(np.var(sizes)))

    plt.xlabel("List indexes")
    plt.ylabel("List sizes")
    plt.title(title)
    plt.legend()

    plt.savefig(''.join([word.capitalize() for word in title.split()]) + ".png")

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

indexes, sizes = parseHashTableStats("fightClubWords.txt.out")

titles = ["Const hash",                 \
          "First char ASCII code hash", \
          "String length hash",         \
          "Char ASCII codes sum hash",  \
          "ROL hash",                   \
          "ROR hash",                   \
          "Polynomial rolling hash"]

hashFunctionCount = len(indexes)
assert(hashFunctionCount == len(sizes))

for hashFunctionIndex in range(hashFunctionCount):
    visualizeStats(indexes[hashFunctionIndex], \
                   sizes[hashFunctionIndex],   \
                   titles[hashFunctionIndex])

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
