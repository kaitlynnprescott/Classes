
def english(one, two):
    xor = one ^ two
    if 32 <= xor <= 122:
        return True
    else:
        return False


def sum_text(mylist):
    mysum = 0
    for i in mylist:
        mysum += i
    return mysum


def xor_decrypt(txt):
    ## don't know what to do here...
    ## read in cipher.txt
    f = open(txt, "r")
    cipher = f.read()
    mylist = cipher.split(',')
    newlist = []
    ## for loop going through possible keys
    ## aaa (979797) to zzz (122122122)
    for i in range(979797, 122122123):
        ## i is the key
        for j in range(len(mylist)):
            ## j is first letter
            if english(i, int(mylist[j])):
                ## xor valid
                newlist.append = i ^ int(mylist[j])
            else:
                for x in newlist:
                    newlist.remove(x)
                break
    print(i)
    print ''.join(newlist)
    print sum_text(mylist)

    f.close()


xor_decrypt("cipher.txt")
