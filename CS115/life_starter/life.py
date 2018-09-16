#
# life.py - Game of Life lab
#
# Name:
#

import random
import sys

def createOneRow(width):
    """ returns one row of zeros of width "width"...  
         You should use this in your
         createBoard(width, height) function """
    row = []
    for col in range(width):
        row += [0]
    return row

def createBoard(width, height):
    ''' returns a 2D array with 'height' rows and 'width' cols'''
    A = []
    for row in range(height):
        A += [createOneRow(width)]
    return A


def printBoard(A):
    ''' this function prints the 2D list of lists
        A without spaces (using sys.stdout.write) '''
    for row in A:
        for col in row:
            sys.stdout.write(str(col))
        sys.stdout.write('\n')

def diagonalize(width, height):
    ''' creates an empty board and then modifies it
        so that it has a diagonal strip of 'on' cells '''
    A = createBoard(width, height)
    for row in range(height):
        for col in range(width):
            if row == col:
                A[row][col] = 1
            else:
                A[row][col] = 0
    return A

def innerCells(width, height):
    ''' creates a board of all live cells (1)
        except for a one-cell-wide border of empty cells (0) '''
    A = createBoard(width, height)
    for row in range(height):
        for col in range(width):
            if row == 0:
                A[row][col] = 0
            elif row == width - 1:
                A[row][col] = 0
            elif col == 0:
                A[row][col] = 0
            elif col == height - 1:
                A[row][col] = 0
            else:
                A[row][col] = 1
    return A

def randomCells(width, height):
    ''' creates an array of randomly assigned 1's and 0's
        except for the outer edge, like innercells. '''
    A = createBoard(width, height)
    for row in range(height):
        for col in range(width):
            if row == 0:
                A[row][col] = 0
            elif row == width - 1:
                A[row][col] = 0
            elif col == 0:
                A[row][col] = 0
            elif col == height - 1:
                A[row][col] = 0
            else:
                A[row][col] = random.choice([0, 1])
    return A

def copy(A):
    ''' make a deep copy of A in newA,
        one that cannot be changed when A changes'''
    newA = createBoard(len(A[0]), len(A))
    for i in range(len(A[0])):
        for j in range(len(A)):
            if A[i][j] == 1:
                newA[i][j] = 1
    return newA

def innerReverse(A):
    ''' switches 0s to 1s and 1s to 0s,
        except for the border of 0s'''
    newA = copy(A)
    for row in range(len(A)):
        for col in range(len(A[0])):
            if row == 0:
                newA[row][col] = 0
            elif row == len(A[0]) - 1:
                newA[row][col] = 0
            elif col == 0:
                newA[row][col] = 0
            elif col == len(A) - 1:
                newA[row][col] = 0
            else:
                if newA[row][col] == 0:
                    newA[row][col] = 1
                else:
                    newA[row][col] = 0
    return newA



def next_life_generation(A):
    ''' Makes a copy of A and then advanced one
        generation of Conway's game of life within
        the *inner cells* of that copy.
        The outer edge always stays 0. '''
    newA = copy (A)
    def countNeighbors(row, col, A):
        count = 0
        y = A[row][col]
        for x in range(row - 1, row + 2):
            for y in range(col - 1, col + 2):
                if A[x][y] == 1:
                    count += 1
        return count
    for row in range(1, len(A[0]) - 1):
        for col in range(1, len(A) - 1):
            if countNeighbors(row, col, A) <= 2:
                newA[row][col] = 0
            if countNeighbors(row, col, A) > 3:
                newA[row][col] = 0
            if countNeighbors(row, col, A) == 3:
                newA[row][col] = 1
    return newA











