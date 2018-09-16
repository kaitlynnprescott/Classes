"""
Name          : boardcutting.py
Author        : Matthew Crepea / Brian S. Borowski
Version       : 1.0
Date          : March 31, 2018
Last modified : April 15, 2018
Description   : Solution to HackerRank -> Algorithms -> Greedy ->
                Cutting Boards
                https://www.hackerrank.com/challenges/board-cutting/problem
"""
MOD_VAL = 1000000007

def board_cutting(cost_y, cost_x):
    """Iterates over cost_y and cost_x, finding the smallest cut along the way
    and adding it to the sum.
    Increments the multiplier in the other direction by 1, as every cut in one
    direction leaves an additional piece in the other.
    """
    x_multiplier = y_multiplier = 1
    total_cost = 0
    cost_x.sort()
    cost_y.sort()
    while cost_x and cost_y:
        if cost_x[-1] >= cost_y[-1]:
            cost = cost_x.pop()
            total_cost += x_multiplier * cost
            y_multiplier += 1
        else:
            cost = cost_y.pop()
            total_cost += y_multiplier * cost
            x_multiplier += 1
    if cost_x:
        total_cost += sum(cost_x) * x_multiplier
    if cost_y:
        total_cost += sum(cost_y) * y_multiplier
    return total_cost % MOD_VAL

if __name__ == '__main__':
    for _ in range(int(input().strip())):
        m, n = input().strip().split(' ')
        m, n = [int(m), int(n)]
        cost_y = list(map(int, input().strip().split(' ')))
        cost_x = list(map(int, input().strip().split(' ')))
        print(board_cutting(cost_y, cost_x))
