#HW4 2017

def rev_comp(s):
    '''returns the reverse complement of s'''
    RC = ""
    for nuc in s:
        if nuc == 'A':
            RC = 'T' + RC
        elif nuc == 'T':
            RC = 'A' + RC
        elif nuc == 'C':
            RC = 'G' + RC
        elif nuc == 'G':
            RC = 'C' + RC
    return RC


def countTATA(DNA):
    ''' Computes number of occurrences of TATA in input string.'''
    counter = 0
    for index in range(len(DNA)):
        if DNA[index:index+4] == 'TATA':
            counter = counter + 1
    return counter


def multiCountTATA( DNAList ):
        ''' Prints the number of occurrences of TATA in each string in the given DNAList.'''
        for DNA in DNAList:
            print( countTATA(DNA) )


print rev_comp ('')
# ''
print rev_comp ('ATTCGTCA')
# 'TGACGAAT'
print rev_comp ('GTCA')
# 'TGAC'

print

print countTATA('')
# 0
print countTATA('CATAGGCTTACC')
# 0
print countTATA('CATATACGGCTATACC')
# 2

print

print multiCountTATA(['CATATACGGCTATACC','ATAGGCTTAGC','TACGGCTATAC'])
# 2
# 0
# 1
print multiCountTATA([])
