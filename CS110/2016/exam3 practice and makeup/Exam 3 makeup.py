def salaryUpdate(l):
    if l == []:
        return []
    else:
       return [l[0][0],1.02*l[0][1]]+salaryUpdate(l[1:])


def path(x,y,L):
    if x == y:
        return True
    elif L == []:
        return False
    else:
        if x == L[0][0]:
            useIt = path(L[0][0],y,L[1:])
            loseIt = path(x,y,L[1:])
            return useIt or loseIt
        else:
            return path(x,y,L[1:])
                    

D = {}     
def subset(target,L):
    if target == 0:
        return True
    elif L == ():
        return False
    elif (target,L) in D.keys():
        return D[(target,L)]
    elif L[0] > target:
         return subset(target,L[1:])
    else:
        useIt = subset(target-L[0],L[1:])
        loseIt = subset(target,L[1:])
        D[(target,L)] = useIt or loseIt
        return useIt or loseIt
    
