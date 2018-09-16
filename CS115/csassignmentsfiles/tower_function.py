'''
Created on Feb 2, 2015

@author: O816
'''
def tower(n):
    if n == 0:
        return 1
    return 2 ** tower(n - 1)

print tower(4)

def tower_reduce(n):
    def power(x,y):
        return y ** x
    return reduce(power, [2] * n)

print tower_reduce(4)