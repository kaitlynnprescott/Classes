D = {}
fileName = 'data.txt'

def read():
    myFile = open(fileName, 'r')
    s = myFile.read()
    L = s.split('\n')
    print L
    for i in range(len(L)):
        x = L[i]
        y = x.split(':')
        D[y[0]] = y[1]
    print D

# for hw, split at comma to get favorite artists



s = '  john  '
d = 'John'
s2 = s.strip() # trim empty spaces
s3 = s2.title() # capitalize


a = 'Artist1,Artist2,Artist3'
L = d.split(',') # splits a string at certain character
