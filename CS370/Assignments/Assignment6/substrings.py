#We pledge our honor that we have abided by the Stevens Honor System.
#Christopher Rudel, Kaitlynn Prescott, Meng Qiu
#substrings.py


def substrings(balls):
    #For a string of length n, contribution by a digit x at
    #position k will be : x* k* 11..1(n-k+1 times '1').
    #Get all digits
    res=0
    f=1
    for i in range(len(balls)-1,-1,-1):
        res=(res+(int(balls[i])-int('0'))*f*(i+1))%(10**9+7)
        f=(f*10+1)%(10**9+7)
    return res
