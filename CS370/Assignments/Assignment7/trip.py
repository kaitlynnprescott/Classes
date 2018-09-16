##########################################################################
## Meng Qui, Chris Rudel, Katie Prescott                                ##
## We pledge our honor that we have abided by the Stevens Honor System. ##
##########################################################################

def main():
    t = int(input())
    # number of test cases
    if t > 10:
        print ("error: number of test cases should be less than 10")
    # while there are still test cases
    while (t >= 1):
        # get first input
        al = input().lower()
        a = len(al)
        while a < 1 or a > 80:
            # make sure it is within 80 characters
            print ("error: alice's list of cities should be between 1 and 80")
            al = input().lower()
            a = len(al)
        # get second input
        bob = input().lower()
        b = len(bob)
        while b < 1 or b > 80:
            # make sure it is within 80 characters
            print ("error: bob's list of cities should be between 1 and 80")
            bob = input().lower()
            b = len(bob)
        
        C = LCS(al, bob)
        allofthem = LCSall(C, al, bob, a, b)
        # sort output
        allofthem=sorted(allofthem)
        # return output
        for i in allofthem:
            print(i)
        t=t-1

def LCS(str1, str2):
    len1 = len(str1)
    len2 = len(str2)
    # An (m+1) times (n+1) matrix
    mylist = [[0] * (len2 + 1) for _ in range(len1 + 1)]
    for i in range(1, len1+1):
        for j in range(1, len2+1):
            if str1[i-1] == str2[j-1]: 
                mylist[i][j] = mylist[i-1][j-1] + 1
            else:
                mylist[i][j] = max(mylist[i][j-1], mylist[i-1][j])
    return mylist

#"LCS all" not "LC Sall"
def LCSall(mylist, str1, str2, i, j):
    def helper(mylist, str1, str2, i, j, memo):
        if (str1, str2,i,j) in memo:
            return memo[(str1, str2,i,j)]
        if i == 0 or j == 0:
            # save result in dictionary
            result = set([""])
        elif str1[i-1] == str2[j-1]:
            result = set([Z + str1[i-1] for Z in helper(mylist, str1, str2, i-1, j-1, memo)])
        else:
            R = set()
            if mylist[i][j-1] >= mylist[i-1][j]:
                R.update(helper(mylist, str1, str2, i, j-1, memo))
            if mylist[i-1][j] >= mylist[i][j-1]:
                R.update(helper(mylist, str1, str2, i-1, j, memo))
            result = R
        #save result in dicitonary
        memo[(str1, str2,i,j)] = result
        return result
    return helper(mylist, str1, str2, i, j, {})

#x="abcabcaa"
#y="acbacba"
#m=len(x)
#n=len(y)
#C=LCS(x,y)
main()
#allofthem = LCSall(C,x,y,m,n)
#allofthem.sort()
#print(allofthem)
