'''
' Name          : alphacode.py
' Author        : Brian S. Borowski
' Version       : 1.0
' Date          : April 17, 2016
' Last modified : April 4, 2017
' Description   : Solves SPOJ's 'Alphacode' problem.
'''

'''
Basic approach to problem:
- Initialize a list of size N with all zeros, but element at index 0 as 1.
- Loop through all the elements
  + If it is a valid single digit number, copy the previous element's value to
    the current element, that is lookup[i] = lookup[i-1].
  + If it is a valid two digit number, add the previous to previous element's
    value to the current element, that is lookup[i] += lookup[i-2].
'''

if __name__ == '__main__':
    encryption = input()
    while encryption != '0':
        length = len(encryption)
        lookup = [0 for _ in range(length)]
        lookup[0] = 1
        i = 1
        while i < length:
            # Check for a valid 1-digit number.
            if encryption[i] != '0':
                lookup[i] = lookup[i - 1]

            # num is used to check if the number formed using 2 digits is 
            # a valid character.
            num = (ord(encryption[i - 1]) - 48) * 10 + ord(encryption[i]) - 48

            # Check for a valid 2-digit number.
            if 10 <= num <= 26:
                lookup[i] += lookup[0 if i - 2 < 0 else i - 2]

            i += 1
        print(lookup[length - 1])
        encryption = input()
