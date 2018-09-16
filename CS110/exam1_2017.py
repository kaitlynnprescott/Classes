##%checked on Picobot
##% 0 ***x -> S 0   
##% 0 ***S -> E 1 
##% 1 x*** -> N 1   



def loginName(first,last):
    if first == '':
        return 'The first name cannot be the empty string'
    elif last == '':
        return 'The last name cannot be the empty string'
    else: return first[0:1]+last[:7]


print loginName('katie', 'prescott')



def doubleTsCounts(s):
    count = 0
    for i in range(len(s)):
        if s[i:i+2] == 'tt':
            count = count+1
    return count

print doubleTsCounts(["pratt", "test", "sttudent", "tablett"])


def doubleTs(s):
    for i in range(len(s)):
        if s[i:i+2] == 'tt':
            return 1
    return 0

def add(x,y):
    return x+y

def DoubleTs(lst):
    if lst == []:
        return 0
    else:
        return reduce(add, map(doubleTs,lst))


    
    
def DoubleTsFor(lst):
    if lst == []:
        return 0
    else:
        count = 0
        for s in lst:
            count = count + doubleTsCounts(s)
    return count


print DoubleTsFor(["pratt", "test", "sttudent", "tablett"])



