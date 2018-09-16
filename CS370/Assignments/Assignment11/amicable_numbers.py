##########################################################################
## Meng Qiu, Christopher Rudel, Kaitlynn Prescott                       ##
## File: amicable_numbers.py                                            ##
## Date: 23 April 2018                                                  ##
## We pledge our honor that we have abided by the Stevens Honor System. ##
##########################################################################
import datetime
sumN = 0
def sum_factors(n):  
     result = []
     for i in range(1, int(n**0.5) + 1): #n**0.5 is significantly faster than n/2
         if n % i == 0:
             result.extend([i, n//i])
     return sum(set(result)-set([n]))

def amicable_pair(number):
    result = []
    global sumN
    for i in range(1,number+1):
        j = sum_factors(i)
        if sum_factors(j) == i and i != j:
            sumN += i
            result.append(tuple(sorted((i,j))))
    return set(result)

start = datetime.datetime.now()
s = amicable_pair(500000)
s = sorted(s)
print('\n'.join(map(str, s)))
print("Sum: " + str(sumN))
a = datetime.datetime.now() - start
timer = int(a.total_seconds()*1000)
elapsed = "{0:.2f}".format(round(timer,2))

print str(elapsed) + " ms"

