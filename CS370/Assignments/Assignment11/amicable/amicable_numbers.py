##########################################################################
## Meng Qiu, Christopher Rudel, Kaitlynn Prescott                       ##
## File: amicable_numbers.py                                            ##
## Date: 23 April 2018                                                  ##
## We pledge our honor that we have abided by the Stevens Honor System. ##
##########################################################################
import datetime

def sum_factors(n):
    result = 0
    for i in range(1, n/2 + 1):
        if n % i == 0:
            result += i
    return result
        

def amicable_pair(number):
    result = 0
    for i in range(1, number):
        if sum_factors(i) > 4:
            if sum_factors(sum_factors(i)) == i and sum_factors(i) != i:
                result += i
                if i < sum_factors(i):
                    print "(" + str(i) + ", " + str(sum_factors(i)) + ")"
    printer = "Sum: "+ str(result)
    return printer


start = datetime.datetime.now()
print (amicable_pair(100000))
a = datetime.datetime.now() - start
timer = int(a.total_seconds()*1000)
elapsed = "{0:.2f}".format(round(timer,2))

print str(elapsed) + " ms"
