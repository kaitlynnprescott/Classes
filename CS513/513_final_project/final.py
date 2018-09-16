# JKLB
# CS 513
# Final Project

from sklearn import tree, cluster, neighbors
import numpy as np
import sys

def printAnimalOptions(labels, animals):
    ret = ""
    for animalInd in xrange(len(labels)):
        if animalInd in animals:
            ret += "\033[33m" + labels[animalInd] + ": " + str(animalInd)
        else:
            ret += labels[animalInd] + ": " + str(animalInd)
        if animalInd % 5 == 4:
            ret += "\n" + "\033[0m"
        else:
            ret += ",\t" + "\033[0m"
    return ret

def knnThing(matrix, labels):

    animals = []

    print "\033[1mYou are going to pick 5 animals that are similar to your chosen animal.  Pick different animals each time and do not pick your chosen animal itself.\033[0m\n"

    inp = -1

    while len(animals) < 5:
        while inp < 0 or inp >= 50 or inp in animals:
            input = raw_input("\nGive the index of one of the following animals:\n" + printAnimalOptions(labels, animals)) + "\n"

            try:
                inp = int(input)
                if inp < 0 or inp >= 50:
                    print "Please give a value between 0 and 49."
                elif inp in animals:
                    print labels[inp] + " has already been selected!"
            except:
                print "Please enter only an integer."
        print "Ok, " + labels[inp] + " saved."
        animals += [inp]
        inp = -1

    counts  = dict()

    animals.sort(reverse = True)

    animalRows = []
    for animal in animals:
        animalRows += [[matrix[animal]]]

    matrix = np.delete(matrix, animals, axis = 0)
    labels = np.delete(labels, animals, axis = 0)

    friendos = neighbors.NearestNeighbors(n_neighbors = 5)
    friendos.fit(matrix)

    for animalRow in animalRows:
        fiveClosest = friendos.kneighbors(animalRow, return_distance = False)[0]
        for closeAnimal in fiveClosest:
            if closeAnimal not in counts:
                counts[closeAnimal] = 1
            else:
                counts[closeAnimal] += 1

    maxInd = max(counts, key = counts.get)

    print "We predict your animal was " + labels[maxInd] + "."

    return


def treeThing(matrix, preds, labels, labelIndexes):
    clf = tree.DecisionTreeClassifier()

    clf.fit(matrix, labelIndexes)

    node = 0

    while clf.tree_.feature[node] != -2:

        inp = ""
        yeasStr = ""
        naysStr = ""

        debug = True
        if debug:
            yeas = []
            nays = []
            for i in xrange(len(clf.tree_.value[node][0])):
                if clf.tree_.value[clf.tree_.children_left[node]][0][i] == 1:
                    nays += [labels[i]]
                elif clf.tree_.value[clf.tree_.children_right[node]][0][i] == 1:
                    yeas += [labels[i]]

            yeasStr = "\nAnimals where this is true:\n[" + ", ".join(yeas) + "]"
            naysStr = "\nAnimals where this is false:\n[" + ", ".join(nays) + "]"

        while inp != "Y" and inp != "N":
            inp = raw_input("\033[1m\033[34m" + preds[clf.tree_.feature[node]] + "\033[0m\n" + yeasStr + "\n"+ naysStr + "\n\n\033[1m\033[34mY/N:\033[0m\n").upper()
            if inp == "Y":
                node = clf.tree_.children_right[node]
            elif inp == "N":
                node = clf.tree_.children_left[node]
            else:
                print "Please enter only Y or N."

    finalInd = np.argmax(clf.tree_.value[node])
    print "Your animal was " + labels[finalInd] + "!"

    clusters = cluster.AgglomerativeClustering(12)
    c = clusters.fit_predict(matrix, labelIndexes)

    actualCluster = c[finalInd]
    thisCluster = []
    for animalInd in xrange(len(c)):
        if c[animalInd] == actualCluster and animalInd != finalInd:
            thisCluster += [labels[animalInd]]
    print "The other similar animals to yours were: "
    print ", ".join(thisCluster)

    return

def main():
    predicates = np.loadtxt("data/predicates.txt", dtype = str)
    animals = np.loadtxt("data/classes.txt", dtype = str)
    matrix = np.loadtxt("data/predicate-matrix-binary.txt", dtype = bool)

    pred = [(int(x), y, z) for x, y, z in predicates]
    inds = [x for x, _, _ in pred]
    preds = [z.replace("+", " ") for _, _, z in pred]

    anims = [(int(x), y) for x, y in animals]
    labelIndexes = [x for x, _ in anims]
    labels = [y.replace("+", " ") for _, y in anims]

    print "Pick one of the following animals:\n"
    print ", ".join(labels) + "\n"

    if len(sys.argv) > 1:
        knnThing(matrix, labels)
    else:
        treeThing(matrix, preds, labels, labelIndexes)
    return

if __name__ == "__main__":
    main()
