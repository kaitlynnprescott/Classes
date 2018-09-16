"""
Name          : chiefhopper.py
Author        : Brian S. Borowski
Version       : 1.0
Date          : March 27, 2018
Description   : Solution to HackerRank -> Algorithms -> Greedy ->
                Chief Hopper

Let:
e = energy
h = height
n = next energy

is e > h? If so, ne = e + (e - h) = 2e - h

is e < h? If so, ne = e - (h - e) = 2e - h

At every iteration, 2e - h >= ne. Solve for e, to enable working backwards.
2e >= ne + h
e >= (ne + h) / 2
e = ceil( (ne + h) / 2 ) = floor( (ne + h + 1) / 2 ) = (ne + h + 1) // 2

We want the final energy to be >= 0. So assume that it is 0, and begin
working backwards, solving for the previous energy based on the next energy.

The value we get at the end of the loop is the minimal starting energy level
required to complete the game, which means to never become negative.
"""
import sys

def chief_hopper(heights):
    energy = 0
    for height in reversed(heights):
        energy = (energy + height + 1) // 2;
    return energy

if __name__ == '__main__':
    _ = int(input().strip())
    heights = list(map(int, input().strip().split(' ')))
    print(chief_hopper(heights))
