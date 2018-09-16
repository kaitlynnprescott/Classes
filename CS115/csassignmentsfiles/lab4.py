'''
Created on Feb 19, 2015

@author: Katie Prescott

I pledge my honor that I have abided by the Stevens Honor System.

** late because I'm at a swim meet in Webster, NY, therefore not at school.

'''
def knapsackhelper(capacity,n,itemlist,L):
    if itemlist == []:
        return [n,L]
    if capacity<= 0:
        return [n,L]
    elif itemlist[0][0]>capacity:
        return knapsackhelper(capacity,0, itemlist[1:],L)
    else:
        loseit = knapsackhelper(capacity,n, itemlist[1:],L)
        useit = knapsackhelper(capacity-itemlist[0][0],n+itemlist[0][1],itemlist[1:],L + [itemlist[0]])
        y = loseit
        x = useit
        if y[0] > x[0]:
            return y
        return x
            

def knapsack(capacity,itemlist):
    return knapsackhelper(capacity,0,itemlist,[])


def fibhelper(n):
    if n == 1:
        return 1
    if n == 2:
        return 1
    return fibhelper(n-1)+fibhelper(n-2)

def fib(n):
    return map(fibhelper,range(1,n+1))
    
