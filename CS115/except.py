import sys

def how_many_years_until(target, current):
    try:
        t = int(target)
    except:
        raise TypeError('Bad value for target: ' + target)
    try:
        c = int(current)
    except:
        raise TypeError('Bad value for current: ' + current)
    return t - c

if __name__ == '__main__':
    try:
        diff = how_many_years_until('100', '3')
        print diff
    except TypeError as error:
        print 'Error:', error
        sys.exit(1)

    age = -1 #ok = False
    while age == -1: #not ok
        str_age = raw_input('Enter your age: ')
        try:
            age = int(str_age)
            #ok = True
        except:
            print 'Error: Age must be an integer.'
    
    next_age = age + 1
    print 'Next year, you will be', next_age, 'years old.'
