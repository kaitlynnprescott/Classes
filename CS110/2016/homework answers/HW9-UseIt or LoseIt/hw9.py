# -*- coding: utf-8 -*-
def subset(n, lst):
    if n == 0:
        return True
    elif lst == []:
        return False
    elif lst[0] > n:
        return subset(n, lst[1:])
    else:
        useIt = subset(n - lst[0], lst[1:])
        loseIt = subset(n, lst[1:])
        return useIt or loseIt


def LCS(s1, s2):
    if s1 == '' or s2 == '':
        return 0
    elif s1[0] == s2[0]:
        return 1 + LCS(s1[1:], s2[1:])
    else:
        option1 = LCS(s1[1:], s2)
        option2 = LCS(s1, s2[1:])
        return max(option1, option2)


def ED(s1, s2):
    if s1 == '':
        return len(s2)
    elif s2 == '':
        return len(s1)
    elif s1[0] == s2[0]:
        return ED(s1[1:], s2[1:])
    else:
        sub = 1 + ED(s1[1:], s2[1:])
        insert = 1 + ED(s1, s2[1:])
        delete = 1 + ED(s1[1:], s2)
        return min(sub, insert, delete)

    
print subset(15, [10, 1, 5])
print LCS('AAC', 'ATA')
print ED('soap', 'sup')
