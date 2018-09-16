'''
Created on Feb 1, 2015

@author: Kaitlynn Prescott
'''
# Factorial
def mult(x,y):
    '''returns product of x and y'''
    return x * y

def factorial(n):
    return reduce(mult, range(1, n + 1))

print factorial(5)

# Mean
def add(x,y):
    '''returns x + y'''
    return x + y

def mean(L):
    return float(reduce(add, L))/len(L)

lst = [1, 3, 4]
print mean(lst)

# Prime
def divides(n):
    def div(k):
        return n % k == 0
    return div




def prime(n):
    ''' returns True if prime'''
     



def prime(n):
    





print prime(5)
print prime(8)
print prime(121)
print prime(853)

