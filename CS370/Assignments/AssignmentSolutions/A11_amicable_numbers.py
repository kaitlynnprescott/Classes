"""
Name          : amicable_numbers.py
Author        : Brian S. Borowski
Version       : 1.0
Date          : April 17, 2018
Last modified : April 20, 2018
Description   : Solution to Project Euler #21
                Amicable Numbers (modified)
"""
from time import time

MAX_VAL = 100000

def compute_sums(divisor_sums, n):
    for i in range(2, n):
        for j in range(i * 2, n, i):
            divisor_sums[j] += i

if __name__ == '__main__':
    start = time()
    sum_amicable = 0
    divisor_sums = [1] * MAX_VAL
    compute_sums(divisor_sums, MAX_VAL)
    amicable = []
    for i in range(2, MAX_VAL):
        a = divisor_sums[i]
        if a < MAX_VAL:
            b = divisor_sums[a]
            if b == i and b != a:
                divisor_sums[a] = 0 # Avoid counting duplicates
                amicable.append('(%d, %d)' % (b, a))
                sum_amicable += a + b
    print('\n'.join(amicable))
    print('Sum:', sum_amicable)
    print('Elapsed time: %.2f ms' % ( (time() - start) * 1000 ) )
