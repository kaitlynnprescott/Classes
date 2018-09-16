def dbl(x):
    """returns 2 * x"""
    return 2*x


def evens(n):
    mylist = range(n+1)
    doubled = map(dbl, mylist)
    return doubled

def evens2(n):
    return map(dbl, range(n))

def add(x, y):
    """ returns x + y"""
    return x + y


def add2(n):
    return n+2


def myfunction(n):
    n = reduce(add, map(add2, range(n+1)))
    return n

def myfunction2(n):
    print n
    mylist = range(n+1)
    print mylist
    list2 = map(add2, mylist)
    print list2
    z = reduce(add, list2)
    return z


print myfunction2(6)






















