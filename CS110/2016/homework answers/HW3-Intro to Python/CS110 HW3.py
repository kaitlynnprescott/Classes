def min_list(lst):
    return min(lst)

lst = [1, 6, 5, 0, 3, -1]
print min_list(lst)
#-1


def add(x, y):
    return x + y

def gauss(N):
    L = range(N + 1)
    return reduce(add, L[:N+1])


print gauss(5)
#15


def sqr(x):
    return x**2

def sumOfSquares(N):
    L = range(N+1)
    return reduce(add, map(sqr, L[:N+1]))
    #return sum(map(sqr, L[:N+1]))


print sumOfSquares(6)
#30
