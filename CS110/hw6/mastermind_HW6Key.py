# -*- coding: utf-8 -*-
# This is the code in the lecture notes

import random

# lets you play the game
def mastermind():
    # takes in how many inputs for colors are allowed
    holes = input("How many holes per row shall we have? ")
    # takes in how many color options there will be
    colors = input ("How many colors shall we have? ")
    # takes in how many times user can guess
    guesses = input("How many guesses shall we have? ")
    # make secret code 
    code = makeRandomCode(holes, colors)
    # initialize guess and board to be empty list, and round to be 1
    guess = []
    board = []
    round = 1
    # as long as the guess is not the same as the randomly generated code
    # and you aren't out of guesses, user can try to guess secret code
    while guess != code and round <= guesses:
        print "Enter your guess for round ", round, "..."
        guess = []
        # read in the guess for each hole and append to guess
        for hole in range(holes):
            guess.append(readGuess(hole, colors))
        # append the guess to the board
        board.append(guess)
        # user did not get it right
        if guess != code:
            # print board and calculate score
            printBoard(board, code, colors)
        round = round + 1
    # loop ends if the user guesses right or runs out of guesses
    if round == 1:
        print "You lucky dog! You guessed right!"
    elif round > guesses:
        print "Sorry, you ran out of guesses."
    else:
        print "You got it in", round-1, "rounds!"


# creates a random list of "colors" the user must guess
# input: number of holes in the game
# input: number of colors being used
# output: randomly chosen code of colors
def makeRandomCode(holes, colors):
    # initialize code to be empty string
    code = []
    # loops through each hole to pick a color
    for position in range(holes):
        # uses random.choice to pick a suitable color 
        code.append(random.choice(range(colors)))
    return code

# reads in the users guess
# input: the hole position the user is currently guessing
# input: number of colors being used
# output: the color guessed by the user at location hole
def readGuess(hole, colors):
    # flag for color being wrong input
    wrongInput = True
    print "Enter your guess from " , range(colors), "for hole ", hole, "..."
    # while user does not have the correct input
    while wrongInput:
        # asks for the color
        guess_color = input()
        if guess_color in range(colors):
            # if the color is acceptable, set the flag to false
            wrongInput = False
        else:
            # otherwise, keep going until color is acceptable
            print guess_color, " is out of range. Please guess from ", range(colors), "..."
    return guess_color

# find all colors from guess that are the right color in the right position
# input: the current guess
# input: the code to be guessed
# input: the number of colors being used
# output: a list of
    # the list of the score,
    # the list of how many of each color were found 
def findBlack(guess, code, colors):
    # initialize found to be a list of 0s with a length of the number of colors
    found = [0] * colors
    # iniitialize score to be a list of dummy valuse of the length of the code
    score = ["dummy"] * len(code)
    # for each hole in the guess 
    for i in range(len(guess)):
        # check if the color is in the right location
        if guess[i] == code[i]:
            # increment the number of that color in found
            found[guess[i]] = found[guess[i]]+1
            # set the score at that location to be black 
            score[i] = "black"
    return [score, found]

# finish the scoring of the guess
# input: the current guess
# input: the code to be guessed
# input: the number of colors being used
# output: a list of the scores
def score_fun(guess,code,colors):
    # what is the score after finding the black scores?
    score_found = findBlack(guess, code, colors)
    # findBlack returns [score, found], separate them
    score = score_found[0]
    found = score_found[1]
    # look at each hole in guess
    for i in range(len(guess)):
        # check if its the same, and do nothing if it is (we already dealt with it)
        if guess[i] == code[i]:
            pass
        # check if the number of times that a specific color is in guess,
        # and see if its the same as or less in the code the user is guessing
        elif how_many_times(guess[i],guess)<= how_many_times(guess[i],code):
            # if the color is in the code more times than in the guess,
            # increment the number of that color in found
            found[guess[i]] = found[guess[i]]+1
            # set the score at that location to be white
            score[i] = "white"
        # if the color is in the guess more than in the code,   
        else:
            # increment the number of that color in found
            found[guess[i]] = found[guess[i]]+1
            # check if the number of times a color has been found is less than
            # the number of times it is in the code
            if found[guess[i]] <= how_many_times(guess[i], code):
                # we have not found all of them yet
                # set the score to be white
                score[i] = "white"
            else:
                # we found all of that color
                # set the score to be empty
                score[i] = "empty"
    return score

# counts how many times x is in a list
# input: something (x) that can be in a list
# input: a list to look through
# output: the number of times it is in the list
def how_many_times(x,lst):
    # initialize count to be 0
    count = 0
    # for each item in the list
    for y in lst:
        if x == y:
            # increment count if it is the same as x
            count = count + 1
    return count

# Prints out all guesses and the scores of each guess
# input: the current board
# input: the code to be guessed
# input: the number of colors being used
# output: Prints the guess and score of each guess the user has made
def printBoard(board, code, colors):
    print("Your Guesses")
    for guess in board:
        print(guess, score_fun(guess, code, colors))
    print("Colors: ", range(colors))
