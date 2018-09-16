

def LCS(s1, s2):
    if s1 == '' or s2 == '':
        return 0
    if s1[0] == s2[0]:
        return 1 + LCS(s1[1:], s2[1:])
    return max(LCS(s1[1:], s2), LCS(s1, s2[1:]))


## memoization:

def fast_LCS(s1, s2):
    def fast_LCS_helper(s1, s2, memo):
        if (s1,s2) in memo:
            return memo[(s1,s2)]
        if s1 == '' or s2 == '':
            result = 0
        elif s1[0] == s2[0]:
            result = 1 + fast_LCS_helper(s1[1:], s2[1:], memo)
        else:
            result = max(fast_LCS_helper(s1[1:], s2, memo), fast_LCS_helper(s1, s2[1:], memo))
            
        memo[(s1,s2)] = result
        return result
    return fast_LCS_helper(s1, s2, {})


def fast_LCS_with_values(s1, s2):
    def fast_values_helper(s1, s2, memo):
        if (s1, s2) in memo:
            return memo[(s1, s2)]
        if s1 == '' or s2 == '':
            result = (0, '')
        elif s1[0] == s2[0]:
            lose_both = fast_values_helper(s1[1:], s2[1:], memo)
            result = (1 + lose_both[0], s1[0] + lose_both[1])
        else:
            use_s2 = fast_values_helper(s1[1:], s2, memo)
            use_s1 = fast_values_helper(s1, s2[1:], memo)
            ## result = use_s1 if use_s1[0] > use_s2[0] else use_s2
            if use_s1[0] > use_s2[0]:
                result = use_s1
            else:
                result = use_s2
                
        memo[(s1,s2)] = result
        return result
    return fast_values_helper(s1, s2, {})





def LIS(s):
    return fast_LCS_with_values(s, ''.join(sorted(s)))


print (LIS('abxzyced'))





