import time

def sumPropDiv(n):
    """returns sum of proper divisors of n"""
    dSum = 0
    for x in range(1, n/2 + 1):
        if n % x == 0:
            dSum += x
    return dSum

def amicSum(number):
    """finds the sum of all amicable numbers less than number, with number greater than 4."""
    answer = 0
    for x in range(4, number):
        if sumPropDiv(x) > 4:
            if sumPropDiv(sumPropDiv(x)) == x and sumPropDiv(x) != x:
                answer += x
                print x, "and", sumPropDiv(x), "are an amicable pair."
    return answer

start = time.time()
print amicSum(10000)
a = time.time() - start
print("{0:.2f}".format(round(a,2)))
