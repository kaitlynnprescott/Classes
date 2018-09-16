def find_motif(m, s):
    count = 0
    i = 0
    for i in range(len(s)):
        if m == s[i: i+len(m)]:
            count += 1
        
    return count

print find_motif("TATA", "GCAAATATAGGGCAATATACTATA")


def winner(ca, lst):
    
    for i in range(len(lst)):
        if lst[i] == ca:
            return i+1
    return "error"

print winner("woody", ["luke", "woody", "dan", "andy", "robin"])


#def lecture_colors(wallc, ceilingc):
    

#print lecture_colors(["grey", "red", "cream"], ["white", "linen"])
