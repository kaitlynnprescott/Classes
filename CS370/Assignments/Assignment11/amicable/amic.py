import time

def sum_factors(self, n):  
    s = 1
    for i in range(2, int(math.sqrt(n))+1):
        if n % i == 0:
            s += i
            s += n/i
    return s

def amicable_pair(self, number):
    result = 0
    for x in range(1,number+1):
        y = self.sum_factors(x)
        if self.sum_factors(y) == x and x != y:
            result += x
    return result


    


start = time.time()
print (amicable_pair([],10000))
print time.time()-start
