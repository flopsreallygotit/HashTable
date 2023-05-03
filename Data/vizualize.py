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

def visualizeStats (indexes, sizes, title, xLimits):
    assert(len(indexes) == len(sizes))

    indexes = np.array(indexes)
    sizes   = np.array(sizes)

    plt.xlim(xLimits)

    plt.bar(indexes, sizes,
            color = "purple",
            label = "Dispersion: " + str(round(np.var(sizes), 2)))

    plt.xlabel("List indexes")
    plt.ylabel("List sizes (Collisions)")
    plt.title(title)
    plt.legend()

    filenameParts = [word.capitalize() for word in title.split()]
    filenameParts[0] = filenameParts[0].lower()
    filename = ''.join(filenameParts)

    plt.savefig("Plots/" + filename + ".png", dpi = 300)
    plt.clf()

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

indexes, sizes = parseHashTableStats("sherlockHolmesWords.txt.out")

titles = ["Const hash",                 \
          "First char ASCII code hash", \
          "String length hash",         \
          "Char ASCII codes sum hash",  \
          "ROL hash",                   \
          "ROR hash",                   \
          "Polynomial rolling hash"]

xLimits = [[0, 10],     \
           [40, 130],   \
           [0, 50],     \
           [0, 1009],   \
           [0, 1009],   \
           [0, 1009],   \
           [0, 1009]]

hashFunctionCount = len(indexes)
assert(hashFunctionCount == len(sizes))

for hashFunctionIndex in range(hashFunctionCount):
    visualizeStats(indexes[hashFunctionIndex], \
                   sizes[hashFunctionIndex],   \
                   titles[hashFunctionIndex],
                   xLimits[hashFunctionIndex])

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
