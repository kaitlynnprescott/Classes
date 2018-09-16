'''
Created on: Apr 28, 2015

@author: Katie Prescott

Pledge: I pledge my honor that I have abided by the Stevens honor system.

CS-115 HW 12
'''

class Board:
    ''' Datatype for a connect four board.'''
    def __init__ (self, width = 7, height = 6):
        ''' constructor'''
        self.width = width
        self.height = height
        for row in range(self.height):
            self.data = [[' '] * width]

    def allowsMove(self, col):
        ''' Checks to see if move can be done. '''
        if col not in range(self.height):
            return False
        for row in range(self.height):
            if self.data[row][col] == ' ':
                return True
        return False

    def addMove(self, col, ox):
        ''' If the move is allowed, then add the move to the board. '''
        if allowsMove(col):
            for row in range(self.height, 0, -1):
                if self.data[row][col] == ' ':
                    self.data[row][col] = ox
                    break
                
    def setBoard(self, move_string):
        ''' Takes in a string of columns and places alternating checkers in
            those colomns, starting with 'X'.
            move_string must be a string of integers.'''
        ox = 'X'
        for col in move_string:
            cols = int(col)
            if 0 <= cols and cols <= self.width:
                self.addMove(col, ox)
            if ox == 'X':
                ox = 'O'
            else:
                ox = 'X'

    def delMove(self, col):
        ''' does the oposite of addMove. '''
        for row in range(self.height, 0, -1):
            if self.data[row][col] == ox:
                self.data[row][col] = ' '

    def winsFor(self, ox):
        ''' Returns True if the given character held in ox has won
            (4 in a row).'''
        def isHorizontalWin(self, ox):
            ''' Checks for a horizontal win. '''
            for row in range(self.height):
                for col in range(self.width - 3):
                    if self.data[row][col] == self.data[row][col + 1] == \
                       self.data[row][col + 2] == self.data[row][col + 3] == ox:
                        return True
            return False
        def isVerticalWin(self, ox):
            ''' Checks for a vertical win. '''
            for col in range(self.width):
                for row in range(self.height - 3):
                    if self.data[row][col] == self.data[row + 1][col] == \
                       self.data[row + 2][col] == self.data[row + 3][col] == ox:
                        return True
            return False
        def isDiagonalWinBack(self, ox):
            ''' Checks for a diagonal win from upper left to lower right. '''
            for row in range(self.height - 3):
                for col in range(self.width - 3):
                    if self.data[row][col] == self.data[row-1][col+1] == \
                       self.data[row-2][col+2] == self.data[row-3][col+3] == ox:
                        return True
            return False
        def isDiagonalWinForward(self, ox):
            ''' Checks for a diagonal win form upper right to lower left. '''
            for row in range(self.height - 3):
                for col in range(self.width - 3):
                    if self.data[row][col] == self.data[row+1][col-1] == \
                       self.data[row+2][col-2] == self.data[row+3][col-3] == ox:
                        return True
            return False

    def hostGame(self):
        ''' play connect four'''
        print 'Welcome to Connect Four!'
        print
        while (1):
            self. __str__()
            xchoice = raw_input("X's Choice: ")
            print xchoice
            if self.allowsMove(xchoice):
                self.addMove(xchoice)
                self.setBoard(self.data)
                if self.winsFor('X'):
                    print 'X wins -- Congratulations!'
                    self. __str__()
                    break
            self. __str__()
            ochoice = raw_input("O's Choice: ")
            print ochoice
            if self.allowsMove(ochoice):
                self.addMove(ochoice)
                self.setBoard(self.data)
                if self.winsFor('O'):
                    print 'O wins -- Congratulations!'
                    self. __str__()
                    break
                self.__str__()
                    
    def __str__(self):
        '''returns a string representation for an object of type Board. '''
        s = ''
        for row in range(self.height):
            s += '|'
            for col in range(self.width):
                s += self.data[row][col] + '|'
            s += '\n'
        s += '-' * self.width + 1
        s += '\n'
        for i in range(self.width):
            s += ' i'
        return s
