def add(x,y):
    return x + y

def gauss(N):
    return reduce(add, range(1, N + 1))

def square(n):
    return n * n

def sum_of_squares (n):
    return reduce(add, map(square, range(1,n + 1)))

def span(lst):
    return reduce(max, lst) - reduce(min, lst)

n = raw_input('Enter your name ')
if n == 'Katie' or n == 'Jane':
    print 'Hooray'
else: 
    print 'Boo'
    
    
    def letter_grade(grade):
        if grade >= 90:
            return 'A'
        elif grade >= 80:
            return 'B'
        elif grade >= 70:
            return 'C'
        elif grade >= 60:
            return 'D'
        else:
            return 'F'
    n = input('Enter your grade')
    print letter_grade (n)
    
    def inverse(n):
        return 1.0/n
    
    def e(n):
        