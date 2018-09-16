def whoistheTA(x):
    if x == "LabA":
        return "Yifan Wang"
    elif x == "LabB":
        return "Kaitlynn Prescott"
    elif x == "LabC":
        return "Cassidy O'Hearn"
    else:
        return "That's not a valid Lab"


def howMany(s, t):
    lenS = len(s)
    lenT = len(t)
    count = 0
    if lenS == 0:
        return "s cannot be empty"
    elif lenT == 0:
        return 0
    else:
        for i in range(lenT):
            if t[i:i+lenS] == s:
                count += 1

        return count


#print howMany('abc', 'aabcbcabc')
        
def x_count_loop(x, lst):
    count = 0
    for i in lst:
        if x == i:
            count += 1
    return count


def add(x, y):
    return x + y

def x_count(z, lst):
    def mapreduce_count(n):
        if n==z:
            return 1
        else:
            return 0
    return reduce(add, map(mapreduce_count,lst))

print x_count('a', ['a', 3, 4, 66, 'b', 'a'])

print x_count('a', [])

