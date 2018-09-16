'''
SPOJ #33 Trip
@author: Brian Borowski

Created on February 24, 2015
Updated for Python 3.x on March 13, 2016
Improvements made on March 20, 2017 and March 27, 2018

'''
def lcs_dp(alice, bob):
    '''Returns a set of strings with characters common to alice and bob.
    Uses bottom-up dynamic programming to improve performance.'''

    def backtrack_all(c, alice, bob, i, j, memo):
        if memo[i][j]:
            return memo[i][j]
        if i == 0 or j == 0:
            result = {''}  # was set(['']) in Python 2
        elif alice[i - 1] == bob[j - 1]:
            result = {s + alice[i - 1] for s in backtrack_all(c, alice, bob, i - 1, j - 1, memo)}
        else:
            result = set() # Backtrack up and to the left to get all solutions.
            if c[i][j - 1] >= c[i - 1][j]:
                result.update(backtrack_all(c, alice, bob, i, j - 1, memo))
            if c[i - 1][j] >= c[i][j - 1]:
                result.update(backtrack_all(c, alice, bob, i - 1, j, memo))
        memo[i][j] = result
        return result

    m = len(alice)
    n = len(bob)
    c = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if alice[i - 1] == bob[j - 1]:
                c[i][j] = c[i - 1][j - 1] + 1
            else:
                c[i][j] = max(c[i][j - 1], c[i - 1][j])
    memo = [[None] * (n + 1) for _ in range(m + 1)]
    return backtrack_all(c, alice, bob, m, n, memo)

def lcs_memo_indexes(alice, bob):
    '''Returns the length of the long common subsequence in strings alice and bob
    as well as a set of strings with characters common to alice and bob.
    Uses memoization to improve performance.'''
    len_alice = len(alice)
    len_bob = len(bob)

    def lcs_helper(alice, bob, alice_start, bob_start, memo):
        # If key exists, return value already associated with key.
        if (alice_start, bob_start) in memo:
            return memo[(alice_start, bob_start)]

        # Do work.
        if alice_start == len_alice or bob_start == len_bob:
            result = (0, {''})
        elif alice[alice_start] == bob[bob_start]:
            lose_both = lcs_helper(alice, bob, alice_start + 1, bob_start + 1, memo)
            result = (1 + lose_both[0], {alice[alice_start] + s for s in lose_both[1]})
        else:
            use_alice = lcs_helper(alice, bob, alice_start, bob_start + 1, memo)
            use_bob = lcs_helper(alice, bob, alice_start + 1, bob_start, memo)
            if use_alice[0] > use_bob[0]:
                result = use_alice
            elif use_alice[0] < use_bob[0]:
                result = use_bob
            else:
                result = (use_alice[0], use_alice[1] | use_bob[1])

        # Store and return result.
        memo[(alice_start, bob_start)] = result
        return result

    return lcs_helper(alice, bob, 0, 0, {})[1]

def lcs_memo_strings(alice, bob):
    '''Returns the length of the long common subsequence in strings alice and bob
    as well as a set of strings with characters common to alice and bob.
    Uses memoization to improve performance.'''

    def lcs_helper(alice, bob, memo):
        # If key exists, return value already associated with key.
        if (alice, bob) in memo:
            return memo[(alice, bob)]

        # Do work.
        if alice == '' or bob == '':
            result = (0, {''})
        elif alice[0] == bob[0]:
            lose_both = lcs_helper(alice[1:], bob[1:], memo)
            result = (1 + lose_both[0], {alice[0] + s for s in lose_both[1]})
        else:
            use_alice = lcs_helper(alice, bob[1:], memo)
            use_bob = lcs_helper(alice[1:], bob, memo)
            if use_alice[0] > use_bob[0]:
                result = use_alice
            elif use_alice[0] < use_bob[0]:
                result = use_bob
            else:
                result = (use_alice[0], use_alice[1] | use_bob[1])

        # Store and return result.
        memo[(alice, bob)] = result
        return result

    return lcs_helper(alice, bob, {})[1]

def merge_lists(list1, list2):
    '''Merges two sorted lists of strings into one.'''
    output = []
    m = len(list1)
    n = len(list2)
    i = 0
    j = 0
    while i < m and j < n:
        if list1[i] < list2[j]:
            output.append(list1[i])
            i += 1
        elif list1[i] > list2[j]:
            output.append(list2[j])
            j += 1
        else:
            output.append(list1[i])
            i += 1
            j += 1
    output.extend(list1[i:])
    output.extend(list2[j:])
    return output
    
def lcs_memo_lists(alice, bob):
    '''Returns the length of the long common subsequence in strings alice and bob
    as well as a list of strings with characters common to alice and bob.
    Uses memoization to improve performance.'''

    def lcs_helper(alice, bob, memo):
        # If key exists, return value already associated with key.
        if (alice, bob) in memo:
            return memo[(alice, bob)]

        # Do work.
        if alice == '' or bob == '':
            result = (0, [''])
        elif alice[0] == bob[0]:
            lose_both = lcs_helper(alice[1:], bob[1:], memo)
            result = (1 + lose_both[0], [alice[0] + s for s in lose_both[1]])
        else:
            use_alice = lcs_helper(alice, bob[1:], memo)
            use_bob = lcs_helper(alice[1:], bob, memo)
            if use_alice[0] > use_bob[0]:
                result = use_alice
            elif use_alice[0] < use_bob[0]:
                result = use_bob
            else:
                result = (use_alice[0], merge_lists(use_alice[1], use_bob[1]))

        # Store and return result.
        memo[(alice, bob)] = result
        return result

    return lcs_helper(alice, bob, {})[1]

if __name__ == '__main__':
    functions = [
        lcs_dp,           # 0, Best
        lcs_memo_indexes, # 1, Even better
        lcs_memo_strings, # 2, Better
        lcs_memo_lists    # 3, Good
    ]
    num_tests = int(input())
    for t in range(num_tests):
        alice = input()
        bob = input()
        # Build a new sorted list from the set of strings.
        for s in sorted(functions[0](alice, bob)):
            print(s)
        if t != 0:
            print()
