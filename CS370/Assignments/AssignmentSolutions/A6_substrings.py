"""
Name          : substrings.py
Author        : Matthew Crepea / Brian Borowski
Version       : 1.1
Date          : February 24, 2018
Last modified : February 25, 2018
Description   : Solution to HackerRank -> Algorithms ->
                Dynamic Programming -> Sam and sub-strings

Idea without modding:
Input string  : 1
previous_count: 1
total         : 1

Input string  : 12
previous count: 1, 10x1 + 2x2 = 14 [2 + 12]
total         : 1, 15

Input string  : 123
previous count: 1, 14, 10x14 + 3x3 = 149 [3 + 23 + 123]
total         : 1, 15, 164

Input string  : 1235
previous count: 1, 14, 140, 10x149 + 4x5 = 1510 [5, 35, 235, 1235]
total         : 1, 15, 164, 1674
"""

MOD_VAL = 1000000007

def substrings(balls):
    balls = [int(x) for x in balls]
    total = previous_count = balls[0]
    
    for i in range(1, len(balls)):
        # At every iteration, find a partial solution for the sum of substrings
        # ending with the ball at index i. This can be done by multiplying the
        # previous count by 10 and adding the number on that ball to all (i + 1)
        # previously generated strings, including the empty string.
        previous_count = (10 * previous_count + (i + 1) * balls[i]) % MOD_VAL
        total = (total + previous_count) % MOD_VAL
        
    return total

if __name__ == '__main__':
    print(substrings(input().strip()))
