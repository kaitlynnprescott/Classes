'''
Created on Feb. 26, 2015
@author:   Katie Prescott
Pledge:    I pledge my honor that I have abided by the Stevens Honor System.

CS115 - Lab 5
'''
import time

words = []
HITS = 10

def fastED(first, second):
    '''Returns the edit distance between the strings first and second. Uses
    memoization to speed up the process.'''
    def fastED_helper(first, second, memo):
        if (first, second) in memo: 
            return memo[(first, second)]
        if first == '':
            result = len(second)
        elif second == '':
            result = len(first)
        elif first[0] == second[0]:
            result = fastED_helper(first[1:], second[1:], memo)
        else:
            sub = 1 + fastED_helper(first[1:], second[1:], memo)
            delete = 1 + fastED_helper(first[1:], second, memo)
            insert = 1 + fastED_helper(first, second[1:], memo)
            result = min(sub, delete, insert)
        memo[(first, second)] = result
        return result
    return fastED_helper(first, second, {})

f = open('3esl.py')
contents = f.read()
words = contents.split('\n')

def getSuggestions(user_input):
    '''For each word in the global words list, determine the edit distance of
    the user_input and the word. Return a list of tuples containing the
    (edit distance, word).
    Hint: Use map and lambda, and it's only one line of code!'''
    return map(lambda x: (fastED(user_input, x), x), words)

def spam():
    '''Main loop for the program that prompts the user for words to check.
    If the spelling is correct, it tells the user so. Otherwise, it provides up
    to HITS suggestions.   
    To exit the loop, just hit Enter at the prompt.'''
        
    while True:
        user_input = raw_input('spell check> ').strip()
        if user_input == '':
            break
        if user_input in words:
            print 'Correct'
        else:
            startTime = time.time()
            suggestions = getSuggestions(user_input)
            suggestions.sort()
            endTime = time.time()
            print 'Suggested alternatives:'
            for suggestion in suggestions[:HITS]:
                print ' %s' % suggestion[1]
            print 'Computation time:', endTime - startTime, 'seconds'
    print 'Bye'

if __name__ == '__main__':
    f = open('3esl.py')
    for word in f:
        words.append(word.strip())
    f.close()
    spam()