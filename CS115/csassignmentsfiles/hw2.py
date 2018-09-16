'''
Created on Feb 10, 2015

@author: Kaitlynn Prescott

I pledge my honor that I have abided by the Stevens honor system.

CS115 - Hw 2
'''
import sys
sys.setrecursionlimit(10000)  # Allows up to 10000 recursive calls; the maximum permitted ranges from system to system



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

def find_match(letter, Dictionary):
    ''' takes letter and finds words that contain it from dictionary'''
    if Dictionary == []:
        return []
    if letter not in Dictionary[0]:
        return find_match(letter, Dictionary[1:])
    return Dictionary[0] + find_match(letter, Dictionary[1:])

def all_words(rack, Dictionary):
    ''' returns all words that contain any letter in a set of letters'''
    if rack == []:
        return []
    if rack != []:
        return find_match(rack[0], Dictionary) + all_words(rack[1:], Dictionary)
    return all_words(rack[1:], Dictionary)

def filter_list(rack, Dictionary):
    ''' returns a filtered list of words based on rack letters'''
    if rack == []:
        return []
    if rack[0] in Dictionary[0]:
        return [Dictionary[0]] + filter_list(rack[1:], Dictionary)
    return filter_list(rack[1:], Dictionary)

def get_out(rack, Dictionary):
    ''' returns words from dictionary that contain letter from rack'''
    if Dictionary == []:
        return []
    if rack[0] in Dictionary[0]:
        return [Dictionary[0]] + get_out(rack[0], Dictionary[1:])
    return get_out(rack[0], Dictionary[1:])

def final(rack, Dictionary):
    ''' returns all words made with a given rack'''
    return get_out(filter_list(rack, Dictionary), Dictionary)

def score(rack):
    ''' returns the scores of available words'''
    if rack == []:
        return []
    y = final(rack, Dictionary)
    return [y[0]] + [wordScore(y[0], scrabbleScores)]

def scoreList(rack):    
    return map(score, rack)
    
def bestWord(rack):
    def better_word(x, y):
        if x[1] > y[1]:
            return x
        return y
    return reduce(lambda x, y: better_word(x, y), scoreList(rack))  




