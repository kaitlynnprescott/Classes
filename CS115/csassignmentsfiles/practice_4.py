'''
Created on Feb 23, 2015

@author: O816
'''
def change(amount, coins):
    ''' given an amount of change and a set of 
    coins, return the number for the smallest 
    amount of coins to make up change.'''
    if amount == 0:
        return 0
    if coins == []:
        return float('inf')
    if coins[0] > amount:
        return change(amount, coins[1:]) 
    else:
        lose_it = change(amount, coins [1:])
        use_it = 1 + change(amount - coins[0], coins)
        return min(lose_it, use_it)

import time

start_time = time.time()
print change(457, [1, 5, 10, 20, 50, 100])
end_time = time.time()
print 'Elapsed time: ', end_time-start_time, 'seconds'
