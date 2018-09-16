import random

def mastermind():
    # initialization
    holes = input("How many holes per row shall we have? ")
    colors = input ("How many colors shall we have? ")
    guesses = input ("How many guesses shall we have?") 
    # make secret code
    code = makeRandomCode(holes, colors)
    guess = []
    board = []
    round = 1
    while guess != code and round<=guesses:
        # get guess from player
        print "Enter your guess for round ", round, "..."
        guess = readGuessHoles(holes,colors)
        board.append(guess)
        # compare guess with secret code and give feedback
        if guess != code:
            printBoard(board, code, colors)
            round = round + 1
    # player guessed the secret code
    # give feedback
    if round ==1:
        print "You lucky dog! You guessed right!"
    elif round<=guesses:
        print "You got it in", round-1, "rounds!"
    else:
        print "Sorry try again next time!"


def makeRandomCode(holes, colors):
    code = []
    for position in range(holes):
        code.append(random.choice(range(colors)))
    return code

def readGuess(hole, colors):
    print "Enter your guess from " , range(colors), "for hole ", hole, "..."
    guess_color = input()
    return guess_color

def readGuessHoles(holes, colors):
    guess = []
    for hole in range(holes):
        guess.append(readGuess(hole, colors))
    return guess
    
    

def findBlack(guess, code, colors):
    found = [0] * colors
    score = ["dummy"] * len(code)
    for i in range(len(guess)): # find all the blacks first!
        if guess[i] == code[i]:
            found[guess[i]] = found[guess[i]]+1   
            score[i] = "black"
    return [score, found]

def score_fun(guess,code,colors):   
    score_found = findBlack(guess, code, colors)
    score = score_found[0]
    found = score_found[1]
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
    
