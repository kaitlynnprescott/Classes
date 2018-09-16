'''
Created on Feb 27, 2015

@author: Katie Prescott

'''
import turtle

def square_spiral(walls):
    def square_spiral_helper(walls, distance, initial, count):
        if walls == count:
            turtle.done
        else:
            turtle.left(90)
            turtle.forward(distance)
            square_spiral_helper(walls, distance + initial * (count % 2), initial, count + 1)
    square_spiral_helper(walls, 20, 20, 0)

square_spiral(50)
