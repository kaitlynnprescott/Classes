'''
Created on Feb 25, 2015

@author: Katie Prescott

Dictionaries & memoization
'''

def distance(first, second):
    if first == '':
        return len(second)
    if second == '':
        return len(first)
    if first[0] == second[0]:
        return distance(first[1:], second[1:])
    substitution = 1 + distance(first[1:], second[1:])
    deletion = 1 + distance(first[1:], second)
    insertion = 1 + distance(first, second[1:]) 
    return min(substitution, deletion, insertion)


def LCS(s1, s2):
    if s1 == '' or s2 == '':
        return 0
    if s1[0] == s2[0]:
        return 1 + LCS(s1[1:], s2[1:])
    return max(LCS(s1[1:], s2), LCS(s1, s2[1:]))

def fast_LCS(s1, s2):
    def fast_LCS_helper(s1, s2, memo):
        if (s1, s2) in memo:
            return memo[(s1, s2)]
        if s1 == '' or s2 == '':
            result = 0
        elif s1[0] == s2[1:]:
            result = 1 + fast_LCS_helper(s1[1:], s2[1:], memo)
        else:
            result = max(fast_LCS_helper(s1, s2[1:], memo), fast_LCS_helper(s1[1:], s2, memo))
        memo[(s1,s2)] = result
        return result
    return fast_LCS_helper(s1, s2, {})

import time

start_time = time.time()
print LCS('helloworld', 'helptheworld')
end_time = time.time()
print 'Elapsed time: ', end_time-start_time, 'seconds'

import time

start_time = time.time()
print fast_LCS('helloworld', 'helptheworld')
end_time = time.time()
print 'Elapsed time: ', end_time-start_time, 'seconds'