'''
Created on Jan 29, 2015

@author: O816
'''
import math
from math import factorial

def add(x,y):
    return x + y



def inverse(n):
        return 1.0/n



def e(n):
    lst = map(factorial, range(1, n+1))
    x = reduce(add, map(inverse, lst))
    return 1 + x

    

def error(n):
    return abs(math.e - e(n))
