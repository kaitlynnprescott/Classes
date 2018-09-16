# Week 9 Exam 2


def pair(a,b):
    if   (a =='A' and b == 'T'):
        return True
    elif  a =='T' and b == 'A':
        return True 
    elif  a =='C' and b == 'G':
        return True
    elif  a =='G' and b == 'C':
        return True
    else:
        return False



def matching_base_pairs(s1,s2):
    if len(s1)!= len(s2):
        print s1, "and", s2, "DNA strings do not have the same length."
    else:
        count = 0
        for i in range(len(s1)):
            if  pair(s1[i], s2[i]):
                count = count + 1
        return count



def how_many_times(x,lst):
    count = 0
    for y in lst:
        if x == y:
            count = count + 1
    return count



def how_many_times_rec(x,lst):
    if lst == []:
        return 0
    else:
        if x == lst[0]:
            return  1 + how_many_times_rec(x,lst[1:])
        else:
            return  how_many_times_rec(x,lst[1:])
