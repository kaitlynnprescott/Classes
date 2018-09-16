# Week 7 Practice exam 2

def mismatched_pairs(s1,s2):
    if len(s1)!= len(s2):
        print s1, "and", s2, "DNA strings do not have the same length."
    else:
        count = 0
        for i in range(len(s1)):
            if not pair(s1[i], s2[i]):
                count = count + 1
        return count

def pair(a,b):
    if (a =='A' and b == 'T'):
        return True
    elif  b =='A' and a == 'T':
        return True
    elif  b =='C' and a == 'G':
        True
    elif  b =='G' and a == 'C':
        return True
    else:
        return False


def pair2(a,b):
    if (a =='A' and b == 'T') or (b =='A' and a == 'T') or (a =='C' and b == 'G')or (a =='G' and b == 'C'):
        return True
    else:
        return False

##
##>>> mismatched_pairs('TCCG', 'ATGCT')
##TCCG and ATGCT DNA strings do not have the same length.
##>>> mismatched_pairs('GTCCG', 'AATTC')
##3
##>>> mismatched_pairs('TAC', 'GCT')
##3
##>>> mismatched_pairs('TACA', 'ATGT')
##0
##
##    
##

def prime(n):
    for d in range(2, n/2+1):
        if n%d == 0:
            return False
    return True
        
def first_n_primes(n,lst):
    count = 0
    index = 0
    while count < n  and index <len(lst):
        if prime(lst[index]):
            print (lst[index])
            count= count+1
        index = index + 1
    if count == 0:
        print "I didn't find any primes."
        return
    else:
        if count < n :
            print "I only found", count, "primes."

##>>> first_n_primes(6,[11,21,3,4,5,62,7,8,49,10,2])
##11
##3
##5
##7
##2
##I only found 5 primes.
##>>> first_n_primes(6,[4,6,8,10,21,76,49])
##I didn't find any primes.
##>>> first_n_primes(4,[11,21,3,4,5,62,7,8,49,10,2])
##11
##3
##5
##7
##>>> 
           
def bands2(singers,drummers,basses,guitars):
    groups=[]
    if singers==[]:
        return 'We cannot form a band without a lead singer.'
    elif drummers == []:
        return 'We cannot form a band without a drummer.'
    elif basses == []:
        return 'We cannot form a band without a bass player.'
    elif guitars == []:
        return 'We cannot form a band without a guitar player.'
    for s in singers:
        for d in drummers:
            for b in basses:
                for g in guitars:
                    groups.append([s,d,b,g])
    return groups


def bands(singers,drummers,basses,guitars):
    if singers==[]:
        return 'We cannot form a band without a lead singer.'
    elif drummers == []:
        return 'We cannot form a band without a drummer.'
    elif basses == []:
        return 'We cannot form a band without a bass player.'
    elif guitars == []:
        return 'We cannot form a band without a guitar player.'
    else:
        band_number = 1
        for s in singers:
            for d in drummers:
                for b in basses:
                    for g in guitars:
                        print band_number,':', s,d,b,g
                        band_number+=1

       
##>>> bands(['Jasmeet', 'Hans', 'Pablo'], ['A.J','Lee'],['Sam', 'Sofia'], ['Daryl', 'Hamid'])
##1 : Jasmeet A.J Sam Daryl
##2 : Jasmeet A.J Sam Hamid
##3 : Jasmeet A.J Sofia Daryl
##4 : Jasmeet A.J Sofia Hamid
##5 : Jasmeet Lee Sam Daryl
##6 : Jasmeet Lee Sam Hamid
##7 : Jasmeet Lee Sofia Daryl
##8 : Jasmeet Lee Sofia Hamid
##9 : Hans A.J Sam Daryl
##10 : Hans A.J Sam Hamid
##11 : Hans A.J Sofia Daryl
##12 : Hans A.J Sofia Hamid
##13 : Hans Lee Sam Daryl
##14 : Hans Lee Sam Hamid
##15 : Hans Lee Sofia Daryl
##16 : Hans Lee Sofia Hamid
##17 : Pablo A.J Sam Daryl
##18 : Pablo A.J Sam Hamid
##19 : Pablo A.J Sofia Daryl
##20 : Pablo A.J Sofia Hamid
##21 : Pablo Lee Sam Daryl
##22 : Pablo Lee Sam Hamid
##23 : Pablo Lee Sofia Daryl
##24 : Pablo Lee Sofia Hamid
##>>> bands([], ['A.J','Lee'],['Sam', 'Sofia'], ['Daryl', 'Hamid'])
##'We cannot form a band without a lead singer.'
##>>> bands(['Jasmeet', 'Hans', 'Pablo'], [],['Sam', 'Sofia'], ['Daryl', 'Hamid'])
##'We cannot form a band without a drummer.'
##>>> bands(['Jasmeet', 'Hans', 'Pablo'], ['A.J','Lee'],['Sam', 'Sofia'], [])
##'We cannot form a band without a guitar player.'
##>>> bands(['Jasmeet', 'Hans', 'Pablo'], ['A.J','Lee'],['Sam', 'Sofia'], [])
##'We cannot form a band without a guitar player.'
