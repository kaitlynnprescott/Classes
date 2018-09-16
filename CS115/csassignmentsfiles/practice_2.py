'''
Created on Feb 6, 2015

@author: O816
'''
def dbl(x):
    return 2 * x

def add(x, y):
    return x + y

lst = [1, 2, 3, 4]




def my_map(f, lst):
    ''' return a list of numbers where function f was applied to an input list '''
    if lst == []:
        return []
    return [f(lst[0])] + my_map(f, lst[1:])
    
print my_map(lambda x: 2 * x, [1, 2, 3, 4])
print my_map(lambda x: x ** 2, [1, 2, 3, 4])
print my_map(lambda x: x / 2.0, [1, 2, 3, 4])
print my_map(lambda x: x ** 2 + 2 * x, [1, 2, 3, 4])

def my_reduce(f, lst):
    if lst == []:
        raise TypeError('my_reduce() of empty sequence with no initial value')
    if lst[:-1] == []:
        return lst[-1]
    return f(my_reduce(f, lst[:-1]), lst[-1])

def div(x, y):
    return x / y

print my_reduce(div, [1.0, 2.0, 3.0, 4.0])
print reduce(div, [1.0, 2.0, 3.0, 4.0])

def power_tail(x,y):
    def power_tail_helper(x, y):
        if y == 0:
            return accum
        return power_tail_helper(x, y - 1, x * accum)    
    return power_tail_helper(x, y, 1)
