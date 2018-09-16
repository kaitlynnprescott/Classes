'''
Created on Feb 15, 2015

@author: O816
'''
scrabbleScores = [ ["a", 1], ["b", 3], ["c", 3], ["d", 2], ["e", 1],
["f", 4], ["g", 2], ["h", 4], ["i", 1], ["j", 8], ["k", 5], ["l", 1],
["m", 3], ["n", 1], ["o", 1], ["p", 3], ["q", 10], ["r", 1], ["s", 1],
["t", 1], ["u", 1], ["v", 4], ["w", 4], ["x", 8], ["y", 4], ["z", 10] ]

Dictionary = ["a", "am", "at", "apple", "bat", "bar", "babble", "can", "foo",
"spam", "spammy", "zzyzva"]

def helper1(scorelist):
    return scorelist[0]

def helper2(scorelist):
    return scorelist[1]

def letterScore(letter, scorelist):
    ''' returns the points won for a letter played based on the scorelist'''
    if scorelist == []:
        return []
    if helper1(scorelist[0]) == letter:
        return helper2(scorelist[0])
    return letterScore(letter, scorelist[1:])

print letterScore('k', scrabbleScores)
print letterScore('a', scrabbleScores)
print letterScore('t', scrabbleScores)
print letterScore('i', scrabbleScores)
print letterScore('e', scrabbleScores)

def wordScore(S, scorelist):
    ''' returns the points won for word played based on the scorelist'''
    if S == '':
        return 0
    return letterScore(S[0], scorelist) + wordScore(S[1:], scorelist)
    

print wordScore('army', scrabbleScores)
print wordScore('apple', scrabbleScores)
print wordScore('babble', scrabbleScores)
print wordScore('zzyzva', scrabbleScores)
print wordScore('katie', scrabbleScores)