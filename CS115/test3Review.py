def merge(L, M, x, m):
    O = []
    L = L[0:x]
    M = M[0:m]
    i = 0
    j = 0
    while i < len(L) and j < len(M):
        if L[i] < M[j]:
            O += [L[i]] # individual elements go in brackets
            i += 1 
        else:
            O += [M[j]]
            j += 1 
    if i > len(L) - 1:
        O += M[j:] # rest is a list, don't need brackets
    else:
        O += L[i:]
    return O
