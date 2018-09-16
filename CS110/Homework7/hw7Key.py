import random

def replace(x, y, lst):
    if lst == []:
        return []
    elif lst[0] == x:
        return [y] + replace(x, y, lst[1:])
    else:
        return [lst[0]] + replace(x, y, lst[1:])


def replaceFirstTwo(x,y,lst):
    return replaceFirstN(x,y,lst,2)


def replaceFirstN(x,y,lst,n):
    if n == 0: return lst
    elif lst == []:
        return []
    elif lst[0] == x:
        return [y] + replaceFirstN(x,y,lst[1:],n-1)
    else:
        return [lst[0]] + replaceFirstN(x,y,lst[1:],n)
        
        

def makeRandomCodeImp(holes, colors):
    code = []
    for position in range(holes):
        code.append(random.choice(range(colors)))
    return code

def makeRandomCode(holes, colors):
    if holes == 0: return []
    else:
        return [random.choice(range(colors))] + makeRandomCode(holes-1, colors)
    

print replace(1,'A',[1,7,3,1])
# ['A', 7, 3, 'A']
print replace(1,'A',[])
# []
print replace(2,'A',[1,7,3,1])
# [1, 7, 3, 1]
print

print replaceFirstN(3,'A',[5,3,6,7,8,3,3,3,9], 2)
# [5, 'A', 6, 7, 8, 'A', 3, 3, 9]
print replaceFirstN(3,'A',[5,3,6,7,8,3,3,3,9], 0)
# [5, 3, 6, 7, 8, 3, 3, 3, 9]
print replaceFirstN(3,'A',[], 6)
# []
print

print makeRandomCode(4,5)
print makeRandomCode(4,5)
print makeRandomCode(4,5)
