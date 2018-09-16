'''
Created on Feb 16, 2015

@author: O816
'''
def take(n, L):
    '''return the list L[0:n]'''
    if L == []:
        return []
    if n == 0:
        return []
    return [L[0]] + take(n-1, L[1:])

# Code to use for testing
def testTake(n,L):
    '''computes L[0:n] using the function above and checks the answer'''
    if take(n,L)==L[0:n]:
        print "test ok"
    else: print "my test failed"


testTake(0, ["not", "it", "works", "!"])
testTake(2, ["not", "it", "works", "!"])
testTake(4, ["not", "it", "works", "!"])

def drop(n, L):
    '''return the list L[n:]'''
    if L == []:
        return []
    if n ==0:
        return L
    y = take(n,L)
    return filter(lambda x: x not in y,L)
    
def testDrop(n,L):
    '''computes L[n:] using the function above and checks the answer'''
    if drop(n,L)==L[n:]:
        print "test ok 2"
    else: print "my test failed 2"

testDrop(0, ["I", "am", "nearly", "done"])
testDrop(1, ["I", "am", "nearly", "done"])
testDrop(3, ["I", "am", "nearly", "done"])