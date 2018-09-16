'''
Created on Mar 3, 2015

@author:   Katie Prescott

Pledge:    I pledge my honor that I have abided by the Stevens Honor System.

CS115 - Hw 5

'''
# import turtle  # Needed for graphics

# Ignore 'Undefined variable from import' errors in Eclipse.

def svTree(trunkLength, levels):
    pass  # TODO

def fastFib(n):
    '''Returns the nth Fibonacci number using the memoization technique
    shown in class and lab. Assume that the 0th Fibonacci number is 0, so
    fastFib(0) = 0,
    fastFib(1) = 1, and
    fastFib(2) = 1'''
    def fastFib_helper(n, memo):
        if (n) in memo:
            return memo[(n)]
        if n == 0:
            result = 0
        elif n == 1:
            result = 1
        elif n == 2:
            result = 1
        else:
            result = fastFib_helper(n-1, memo) + fastFib_helper(n-2, memo)
        memo[(n)] = result
        return result
    return fastFib_helper(n, {}) 
            

# If you did this correctly, the results should be nearly instantaneous.
print fastFib(3)  # 2
print fastFib(5)  # 5
print fastFib(9)  # 34
print fastFib(24)  # 46368
print fastFib(40)  # 102334155
print fastFib(50)  # 12586269025

import turtle

def svTree(trunk_length, branches):
    if branches == 0:
        return
    turtle.forward(trunk_length)
    turtle.right(45)
    svTree(trunk_length / 2, branches - 1)
    turtle.left(90)
    svTree(trunk_length / 2, branches - 1)
    turtle.right(45)
    turtle.backward(trunk_length)
    return
# Should take a few seconds to draw a tree.
svTree(100, 4)