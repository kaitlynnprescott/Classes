# -*- coding: utf-8 -*-
def replace(x, y, lst):
    if lst == []:
        return []
    elif lst[0] == x:
        return [y] + replace(x, y, lst[1:])
    else:
        return [lst[0]] + replace(x, y, lst[1:])


def prime(n):
    for d in range(2, n/2+1):
        if n%d == 0:
            return False
    return True
        
def first_n_primes(n, lst):
    return prime_helper(n, lst, 0)

def prime_helper(n, lst, count):
    if n == count:
        return
    elif lst == []:
        if count == 0:
            print "I didn't find any primes."
        else:
            print "I only found ", count, " primes."
        return
    else:
        if prime(lst[0]):
            print lst[0]
            count = count + 1
        prime_helper(n, lst[1:], count)

def findBlack(code, guess, colors):
    return black_helper(code, guess, [], colors * [0])

def black_helper(code, guess, matches, color_counts):
    if code == []:
        return [matches, color_counts]
    elif code[0] == guess[0]:
        color_counts[code[0]] = color_counts[code[0]] + 1
        return black_helper(code[1:], guess[1:], matches + ['black'], color_counts)
    else:
        return black_helper(code[1:], guess[1:], matches + ['dummy'], color_counts)

print replace(1,2,[1,2,3,1])
#[2, 2, 3, 2]
print replace(1,2,[])
#[]
print replace (4,5,[1,4,2])
#[1, 5, 2]

print first_n_primes(6,[4,6,8,10,21,76,49])
#I didn’print findBlack([1,2,3],[3,2,1],6)
#[[’dummy’, ’black’, ’dummy’], [0, 0, 1, 0, 0, 0]]
print findBlack([1,1,2,4,4,5],[1,1,5,4,4,0],6)
#[[’black’, ’black’, ’dummy’, ’black’, ’black’, ’dummy’], [0, 2, 0, 0, 2, 0]]
print findBlack([1,1,2,4,4,5],[1,1,5,4,4,5],6)
#[[’black’, ’black’, ’dummy’, ’black’, ’black’, ’black’], [0, 2, 0, 0, 2, 1]]
t find any primes.
print  first_n_primes(6,[11,21,3,4,5,62,7,8,49,10,2])
#11
#3
#5
#7
#2
#I only found 5 primes.
print first_n_primes(3,[11,21,3,4,5,62,7,8,49,10,2])
#11
#3
#5

print findBlack([1,2,3],[3,2,1],6)
#[[’dummy’, ’black’, ’dummy’], [0, 0, 1, 0, 0, 0]]
print findBlack([1,1,2,4,4,5],[1,1,5,4,4,0],6)
#[[’black’, ’black’, ’dummy’, ’black’, ’black’, ’dummy’], [0, 2, 0, 0, 2, 0]]
print findBlack([1,1,2,4,4,5],[1,1,5,4,4,5],6)
#[[’black’, ’black’, ’dummy’, ’black’, ’black’, ’black’], [0, 2, 0, 0, 2, 1]]
