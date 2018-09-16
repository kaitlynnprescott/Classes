def replace_loop(x, y, lst):
    for i in range(len(lst)):
        if lst[i] == x:
            lst[i] = y

    return lst


def replace_map(x, y, lst):
    def replacex(n):
        if n == x:
            return y
        return n
    return map(replacex, lst)

def x_count_loop(x, lst):
    count = 0
    for i in range(len(lst)):
        if lst[i] == x:
            count = count + 1
    return count

def add(x, y):
    return x + y

def x_count_map(x, lst):
    def is_x(n):
        if n == x:
            return 1
        return 0
    return reduce(add, map(is_x, lst))



print replace_loop(1, 2, [1, 2, 3, 1])
#[2, 2, 3, 2]
print replace_map(1, 2, [1, 2, 3, 1])
#[2, 2, 3, 2]
print x_count_loop("a", ["a", 3, 4, 66, "b", "a"])
#2
print x_count_map("a", ["a", 3, 4, 66, "b", "a"])
#2


## mystery(3):
##    for d in range(2, 3):
##        d = 2:
##            3%2 = 1
## return true
