# mandelbrot.py
# Lab 8
#
# Name:

# keep this import line...
from cs5png import *

# start your Lab 8 functions here:
def mult(c, n):
    ''' mult uses only a loop and addition to multiply c by the integer n'''
    result = 0
    for i in range(n):
        result = result + c
    return result

def update (c, n):
    ''' update starts z = 0 and runs z = z**2 + c
        for a total of n times. It returns the final z. '''
    z = 0
    for i in range(n):
        z = z**2 + c
    return z

def inMSet(c, n):
    ''' Takes in a complex number, c, and an integer, n. 
    Returns True if c is in the Mandelbrot set, and False otherwise.
        inMSet takes in 
            c for the update step of z = z**2 +c
            n, the max number of times to run that step
        Then, it should return
            False as soon as abs(z) gets larger than 2
            True if abs(z) never gets larger than 2 (for n iterations)'''
    z = 0
    for i in range(n):
        z = z**2 + c
        if abs(z) > 2:
            return False
    return True

def weWantThisPixel( col, row ):
    """ a function that returns True if we want
    the pixel at col, row and False otherwise
    """
    if col%10 == 0 or row%10 == 0:
        return True
    else:
        return False
    
def test():
    """ a function to demonstrate how
    to create and save a png image
    """
    width = 300
    height = 200
    image = PNGImage(width, height)

    # create a loop in order to draw some pixels

    for col in range(width):
        for row in range(height):
            if weWantThisPixel( col, row ) == True:
                image.plotPoint(col, row)
    image.saveFile() # we looped through every image pixel; we now write the file

    ''' if col % 10 and row % 10 was changed to
           col % 10 or row % 10, then it would change from
           a plot grid of points to a plot grid of lines. '''

def scale(pix, pixelMax, floatMin, floatMax):
    ''' Scale takes in
            pix, the CURRENT pixel column, or row
            pixelMax, the total # of pixel columns
            floatMin, the min floating point value
            floatMax, the max floating point value
        scale returns the floating point value that
        corresponds to pix
        '''
    return (float(pix) / pixelMax) * (floatMax - floatMin) + floatMin

def mset():
    ''' creates a 300x200 image of the Mandelbrot set '''
    width = 300
    height = 200
    image = PNGImage(width, height)

    #create a loop in order to draw some pixels

    for col in range(width):
        for row in range(height):
            x = scale(col, width, -2.0, 1.0)
            y = scale(row, height, -1.0, 1.0)
            c = x + y*1j
            if inMSet(c, 100) == True:
                image.plotPoint(col, row)
    image.saveFile()
