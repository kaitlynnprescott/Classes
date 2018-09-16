'''
Created on Feb 23, 2015

@author: Katie Prescott

I pledge my honor that I have abided by the Stevens Honor System.

'''
def pascal_row(n):
    ''' Return the nth row of Pascal's Triange'''
    if n == 0:
        return [1]
    if n == 1:
        return [1, 1]
    else:
        line = [1]
        line_before = pascal_row(n - 1)
        for i in range(len(line_before) - 1):
            line.append(line_before[i] + line_before[i + 1])
        line = line + [1]
    return line

def pascal_triangle(n):
    '''return Pascal's triangle in a list of lists
    up to and including the nth row'''
    if n == 0:
        return [[1]]
    return pascal_triangle(n-1) + [pascal_row(n)]

print pascal_row(3)
print pascal_triangle(3) 
    
