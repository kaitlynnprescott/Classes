'''
Created on Feb 4, 2015

@author: Kaitlynn Prescott
'''
def length(lst):
    ''' Return the length of the list.'''
    if lst == []:
        return 0
    return 1 + length(lst[1:])

print length([1, 2, 3, 4]) 

def reverse(lst):
    ''' Returns a new list that is the reverse of the input list'''
    if lst == []:
        return []
    return [lst[-1]] + reverse(lst[:-1])

print reverse([4, 3, 2, 1])
print reverse([1, [2, [3, 4], [5, [6,7], 8]]])

def member(x, lst):
    if lst == []:
        return False
    if lst[0] == x:
        return True
    return member(x, lst[1:])

print member(9, [1, 2, 9, 5, 7])

def collapse(lst):
    if lst == []:
        return []
    if isinstance(lst[0], list):
        return collapse(lst[0]) + collapse(lst[1:])
    return [lst[0]] + collapse(lst[1:])

print collapse([2, 4, [8, [3]]])

def fib(n):
    if n <= 1:
        return n
    return fib(n-1) + fib(n-2)
