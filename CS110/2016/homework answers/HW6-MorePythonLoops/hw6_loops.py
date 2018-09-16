def double_strand(s1, s2):
    if len(s1) != len(s2):
        return False
    strand = True
    for i in range(len(s1)):
        if s1[i] == 'A':
            if s2[i] == 'T':
                strand = True
            else:
                strand = False
                return strand
        elif s1[i] == 'T':
            if s2[i] == 'A':
                strand = True
            else:
                strand = False
                return strand
        elif s1[i] == 'C':
            if s2[i] == 'G':
                strand = True
            else:
                strand = False
                return strand
        elif s1[i] == 'G':
            if s2[i] == 'C':
                strand = True
            else:
                strand = False
                return strand
        else:
            strand = False
            return strand
    return strand

print double_strand('ATTCGTCA','TAAGCAGT')
#true
print double_strand('TTCGTCA','CAGT')
#false
print double_strand('TTCA','CAGT')
#false
