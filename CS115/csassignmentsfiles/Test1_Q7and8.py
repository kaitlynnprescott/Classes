'''
Created on Feb 23, 2015

@author: Katie Prescott

Pledge: I pledge my Honor that I have abided by the Stevens Honor System.

'''
def keep_excitement_rec(lst):
    ''' Assume lst is a list of non-empty strings.
    Return a list of strings with only those words starting and ending in an 
    exclamation mark, such as !yay! '''
    if lst == []:
        return []
    return ['!' + lst[0] + '!'] + keep_excitement_rec(lst[1:])

def keep_excitement_fil(lst):
    '''Same as keep_excitement_rec'''
    return filter(lambda x: '!' + x + '!', lst)
