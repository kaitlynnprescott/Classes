# This solution doesn't have a separate function findBlack, instead it embeds
# the code within score_fun.

import random

def mastermind():
    holes = input("How many holes per row shall we have? ")
    colors = input ("How many colors shall we have? ")
    # make secret code
    code = makeRandomCode(holes, colors)
    guess = []
    board = []
    round = 1
    # try to guess secret code
    while guess != code:
        print "Enter your guess for round ", round, "..."
        guess = []
        for hole in range(holes):
            guess.append(readGuess(hole, colors))
        board.append(guess)
        if guess != code:
            # print board and calculate score
            printBoard(board, code, colors)
        round = round + 1
    if round ==1:
        print "You lucky dog! You guessed right!"
    else:
        print "You got it in", round-1, "rounds!"

def makeRandomCode(holes, colors):
    code = []
    for position in range(holes):
        code.append(random.choice(range(colors)))
    return code

def readGuess(hole, colors):
    print "Enter your guess from " , range(colors), "for hole ", hole, "..."
    guess_color = input()
    return guess_color

def score_fun(guess,code,colors):
    score = ["dummy"] * len(code)
    found = [0] * colors
    for i in range(len(guess)): # find all the blacks first!
        if guess[i] == code[i]:
            found[guess[i]] = found[guess[i]]+1   
            score[i] = "black"
    for i in range(len(guess)):
        if guess[i] == code[i]:
            pass 
        elif how_many_times(guess[i],guess)<= how_many_times(guess[i],code):
            found[guess[i]] = found[guess[i]]+1   
            score[i] = "white"
        # how_many_times(guess[i],guess) > how_many_times(guess[i],code)    
        else:
            found[guess[i]] = found[guess[i]]+1   
            if found[guess[i]] <= how_many_times(guess[i], code):
                # we have not found all of them yet
                score[i] = "white"
            else:
                score[i] = "empty"
    return score
   
def how_many_times(x,lst):
    count = 0
    for y in lst:
        if x == y:
            count = count + 1
    return count
    
def printBoard(board, code, colors):
    print("Your Guesses")
    for guess in board:
        print(guess, score_fun(guess, code, colors))
    print("Colors: ", range(colors))
