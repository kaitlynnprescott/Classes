'''
Created on Feb 12, 2015

@author: Kaitlynn Prescott

I pledge my honor that I have abided by the Stevens Honor System.
'''
def change(amount, coins):
    ''' given an amount of change and a set of 
    coins, return the number for the smallest 
    amount of coins to make up change.'''
    if amount == 0:
        return 0
    if coins == []:
        return float('inf')
    if coins[0] > amount:
        return change(amount, coins[1:]) 
    else:
        lose_it = change(amount, coins [1:])
        use_it = 1 + change(amount - coins[0], coins)
        return min(lose_it, use_it)
    
def give_change_helper(amount, coins, n, L):
    if coins == []:
        return [float('inf'), []]
    if amount == 0:
        return [0, []]
    elif coins[0] > amount:
        return give_change_helper(amount, coins[1:], n, L)
    else: 
        lose_it = give_change_helper(amount, coins[1:], n, L)
        use_it = give_change_helper(amount - coins[0], coins, n + 1, L + [coins[0]])
        return min(lose_it, use_it)
            
def give_change(amount, coins):
    if amount == 0:
        return [0, []]
    if coins == []:
        return [float('inf'), []]
    if coins[0] > amount:
        return give_change(amount, coins[1:])
    return give_change_helper(amount, coins[1:])
        
    print give_change(48, [1, 5, 10, 25, 50])
    
    
    #problem 1  
scrabbleScores = [ ['a', 1], ['b', 3], ['c', 3], ['d', 2], ['e', 1], ['f', 4], ['g', 2],
    ['h', 4], ['i', 1], ['j', 8], ['k', 5], ['l', 1], ['m', 3], ['n', 1],
    ['o', 1], ['p', 3], ['q', 10], ['r', 1], ['s', 1], ['t', 1], ['u', 1],
    ['v', 4], ['w', 4], ['x', 8], ['y', 4], ['z', 10] ]

Dictionary = ['a', 'am', 'at', 'apple', 'bat', 'bar', 'babble', 'can', 'foo',
              'spam', 'spammy', 'zzyzva']

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

def wordScore(S, scorelist):
    ''' returns the points won for word played based on the scorelist'''
    if S == '':
        return 0
    return letterScore(S[0], scorelist) + wordScore(S[1:], scorelist)

print wordScore('babble', scrabbleScores)

def word_with_score(dct, scores):
    '''list of words in dct with their scrabble score'''
    if dct == []:
        return []
    return [[dct[0], wordScore(dct[0], scores)]] + word_with_score(dct[1:], scores)

print word_with_score(Dictionary, scrabbleScores)

#problem 2
def take(n, L):
    if L == []:
        return []
    if n == 0:
        return L[0]
    return [L[0]] + take(n-1, L[1:])


# problem 3
def drop(n,L):
    if L == []:
        return []
    if n == 0:
        return L
    y = take(n,L)
    return filter(lambda x: x not in y, L)

