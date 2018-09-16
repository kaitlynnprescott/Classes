'''
Created on Feb 5, 2015

@author: Kaitlynn Prscott
'''
# dot(L, K)
def dot(L, K):
    '''returns the dot product of L and K'''
    if L == [] or K == []:
        return 0.0
    return (L[0] * K[0]) + dot(L[1:], K[1:])
    

print dot([5, 3], [6, 4])

# explode(S)
def explode(S):
    '''returns S separated into a list of strings of length 1'''
    if S == '':
        return []
    return [S[0]] + explode(S[1:])

print explode('spam')

#ind(e, L)
def ind(e, L):
    '''returns the index where e is first found in L'''
    if L == [] or L == '' or L[0] == e:
        return 0
    return 1 + ind(e, L[1:])

print ind(2, [])
print ind(42, range(0, 100))
print ind('i', 'team')

#removeAll(e, L) 
def removeAll(e, L):
    '''returns L with all instances of e in L removed'''
    if L == []:
        return []
    return L[0:ind(e, L)] + removeAll(e, L[(ind(e, L) + 1):])  
        
print removeAll(42, [55, 77, 42, 11, 42, 88])

#myfilter(L)
def myFilter(f, L):
    '''returns numbers that fit requirements'''
    if L == []:
        return []
    if f(L[0]) == True:
        return [L[0]] + myFilter(f, L[1:])
    if f(L[0]) == False:
        return myFilter(f, L[1:])
        
def even(X):
    if X % 2 == 0: 
        return True 
    return False
     
print myFilter(even, [0, 1, 2, 3, 4, 5, 6])

#deepReverse
def deepReverse(L):
    '''returns a new list that is the reversal of the input list'''
    if L == []:
        return []
    if isinstance(L[-1], list):
        return [deepReverse(L[-1])] + deepReverse(L[:-1])
    return [L[-1]] + deepReverse(L[:-1])

print deepReverse([1, [2, [3, 4], [5, [6, 7], 8]]])
print deepReverse([1, [2, 3], 4])
# does it need to keep brackets?

