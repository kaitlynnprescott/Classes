#(1,(7,(6,(),()),(8,(),()),(2,(6),(),()),(3,(5,(),()),(9,(),()))

def leaf(t):
    if t[1]==() and t[2]==():
        return True
    else:
        return False
    
def SumTree(t):
    if leaf(t):
        return t[0]
    else:
        return t[0]+SumTree(t[1])+SumTree(t[2])

def mirrorTree(t):
    if leaf(t):
        return t
    else:
        return t[0], mirrorTree(t[2]),mirrorTree(t[1])

def size(t):
    if leaf(t):
        return 1
    else:
        return 1 + size(t[1]) + size(t[2])
    
def averageTree(t):
    if leaf(t):
        return t[0]
    else:
        return (SumTree(t)/size(t))


print SumTree((1,(5,(7,(),()),(62,(),())),(2,(12,(),()),(24,(),()))))
#113
print SumTree((11, (), ()))
#11

print averageTree((5,(1,(67,(),()),(2,(),())),(3,(10,(),()),(26,(),()))))
#16
print averageTree((6, (), ()))
#6

print mirrorTree(('ATG',('GGCT',(7, (), ()),(62, (), ())),('TTA',(12, (), ()),(24, (), ()))))
#('ATG',('TTA',(24, (), ()),12, (), ())),('GGCT',(62, (), ()),(7, (), ())))
print mirrorTree((12, (), ()))
#(12,(),())
