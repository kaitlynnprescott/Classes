def head(lst):
    ''' Write a function called head that returns the first element
        of a list and the message "ERROR: The empty list has no head"
        if the list is empty. '''
    if lst == []:
        return "ERROR: The empty list has no head"
    else:
        return lst[0]




def tail(lst):
    ''' Write a function tail(lst) that returns a new list obtained from
        lst by removing its first element and the messege "ERROR: The empty
        list has no tail" if the list is empty. '''
    if lst == []:
        return "ERROR: The empty list has no tail"
    else:
        return lst[1:]




def replace_and_triple(x, y, z, lst):
    ''' Write a function replace_and_triple(x, y, z, lst) that returns
        the result of replacing every x by y and every z by 3*z in lst
        if z!= z, and if z = x it returns lst. '''
    def change2x(n):
        if n == x:
            return y
        else:
            return n
    def change2z(n1):
        if n1 == z:
            return z*3
        else:
            return n1
    return map(change2z, map(change2x, lst))
        

        
    '''   
        for i in range(len(lst)):
            if lst[i] == x:
                lst[i] = y
            elif lst[i] == z:
                lst[i] = 3*z
        return lst
    '''


print head([])
# ERROR
print head([23, 4, 66])
# 23
print

print tail([])
# ERROR
print tail([23, 4, 66])
# [4, 66]
print

print replace_and_triple(1, 7, 5, [1, 4, 3, 1, 5, 20, 5])
# [7, 4, 3, 7, 15, 20, 15]
print replace_and_triple(21, 4, 7,  [])
# []
print replace_and_triple(2, 5, 2, [3, 6, 2, 7, 5, 8, 10])
# [3, 6, 2, 7, 5, 8, 10]
