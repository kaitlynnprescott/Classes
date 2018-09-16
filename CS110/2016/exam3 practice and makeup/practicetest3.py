#1
def minim(L):
    if L == []:
        return "There is no minimum of an empty list"
    else:
        return minHelper(L, L[0])

def minHelper(L, minNum):
    if(len(L) == 0):
        return minNum
    else:
        if(L[0] < minNum):
            return minHelper(L[1:], L[0])
        else:
            return minHelper(L[1:], minNum)

print minim([13, 21, 53, 4])
print minim([12, -10, 16])
print minim([])


#2
def succ(n):
    if n == 0:
        return 1
    else:
        return 1 + succ(n-1)

print succ(23)
print succ(0)

#3
def bump(lst):
    if lst == []:
        return []
    else:
        return [lst[0]+1] + bump(lst[1:])

print bump([134, 2, 43, 76, 25])
print bump([])

#4
def member(n, lst):
    if lst == []:
        return False
    else:
        if n == lst[0]:
            return True
        else:
            return member(n, lst[1:])

#5 Hand trace

#6
def uniquefy(lst):
    if lst == []:
        return ''
    if len(lst) == 1:
        return [lst[0]]
    elif lst[0] in lst[1:]:
        return uniquefy(lst[1:])
    else:
        return [lst[0]] + uniquefy(lst[1:])


print uniquefy([21, 12, 23, 12, 6, 13, 12])
print uniquefy([12, 6, 5, 12, 'a', 'b', 'a'])
print uniquefy([])


#7
def pal(s):
    if len(s) < 2:
        return True
    if s[0] != s[-1]:
        return False
    return pal(s[1:-1])



#8
def evens(lst):
    if lst == []:
        return []
    else:
        if lst[0]%2 == 0:
            return [lst[0]] + evens(lst[1:])
        else:
            return evens(lst[1:])

print evens([10, 3, 5, 6, 23, 7])
print evens([])


#9
def snack(n,lst):
    if lst == []:
        return 0
    elif n == 0:
        return 0
    else:
        loseit = snack(n,lst[1:])
        if lst[0] > n:
            return loseit
        useit = 1 + snack(n - lst[0], lst)
        if useit > loseit:
            return useit
        else:
            return loseit

print '#9'
print snack(24, [])
print snack(22, [10, 4])
print snack(33, [5, 4, 8, 10])


#10
def subset(target, L):
    if target == 0:
        return True
    elif L == []:
        return False
    elif L[0] > target:
        return subset(target, L[1:])
    else:
        use_it = subset(target - L[0], L[1:])
        lose_it = subset(target, L[1:])
        return use_it or lose_it

#11
D = {}
def subset1(target,L):
    if target == 0:
        return True
    elif L == []:
        return False
    elif (target,L) in D:
        return D[(target,L)]
    elif L[0] > target:
        result = subset1(target,L[1:])
    else:
        useit = subset1(target - L[0],L[1:])
        loseit = subset1(target,l[1:])
        result = useit or loseit
    D[(target,L)] = result
    return result
