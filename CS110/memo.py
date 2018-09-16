def memoizedChange( amount, coins, memo ):
    ''' Returns the least number of coins required to make the
        given amount using the tuple of provided denominations.'''
    if amount == 0: return 0
    elif coins== ():  return float('infinity')
    # Since the base cases don't apply, check the memo
    # to see if we've solved this problem before.
    elif (amount, coins) in memo:
        return memo[(amount, coins)]
    elif coins[0] > amount:
        # the key (amount, coins) is not in memo
        solution = memoizedChange(amount, coins[1:], memo)
        memo[(amount, coins)] = solution
        return solution
    else:
        useIt = 1 + memoizedChange(amount - coins[0], coins, memo)
        loseIt = memoizedChange(amount, coins[1:], memo)
        solution = min(useIt, loseIt)
        memo[(amount, coins)] = solution
        return solution 

memo = {}
 
