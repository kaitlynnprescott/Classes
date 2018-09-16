import math
import turtle

from Matrix import *
from Vector import *

class Shape(object):
    def __init__(self):
        self.points = []
        
    def render(self):
        '''Use turtle graphics to render shape.'''
        turtle.penup()
        turtle.setposition(self.points[0].x, self.points[0].y)
        turtle.pendown()
        turtle.fillcolor(self.color)
        turtle.pencolor(self.color)
        turtle.begin_fill()
        for vector in self.points[1:]:
            turtle.setposition(vector.x, vector.y)
        turtle.setposition(self.points[0].x, self.points[0].y)
        turtle.end_fill()

    def erase(self):
        '''Draw shape in white to effectively erase it from screen.'''
        temp = self.color
        self.color = 'white'
        self.render()
        self.color = temp
    
    def rotate(self, theta, rotateAbout = Vector(0, 0)):
        '''Rotate shape by theta degrees.'''
        theta = math.radians(theta)  # THIS IS CORRECT!
        # Python's trig functions expect input in radians,
        # so this function converts from degrees into radians.
        self.translate(rotateAbout.x, rotateAbout.y)
        RotationMatrix = Matrix(math.cos(theta), -1*math.sin(theta), math.sin(theta), math.cos(theta))
        NewPoints = []
        for vector in self.points:
            newvector = RotationMatrix * vector
            NewPoints.append(newvector)
        self.points = NewPoints
        self.translate(-rotateAbout.x, -rotateAbout.y)

    def translate(self, x, y):
        for i in range(len(self.points)):
            self.points[i].x = self.points[i].x + x
            self.points[i].y = self.points[i].y + y

    def scale(self, s):
        for i in range(len(self.points)):
            self.points = self.points * s 

    def flip(self, p1, p2): 
        center = Vector((p2.x-p1.x)/2., (p2.y+p1.y)/2)
        a = float(p2.x-p1.x)
        b = float(p2.y-p1.y)
        theta = math.degrees(math.asin(a/((a**2+b**2)**.5)))
        FlipMatrix = Matrix(1,0,0,-1)
        NewPoints = []
        self.rotate(theta, center)
        for point in self.points: 
            NewPoints.append(FlipMatrix * point)
        self.points = NewPoints
        self.flip(-1*theta, center)
        
            
class Rectangle(Shape):
    def __init__(self, width, height, center = Vector(0, 0), color = 'black'):
        SW = Vector(center.x - width/2.0, center.y - height/2.0)
        NW = Vector(center.x - width/2.0, center.y + height/2.0)
        NE = Vector(center.x + width/2.0, center.y + height/2.0)
        SE = Vector(center.x + width/2.0, center.y - height/2.0)
        self.points = [SW, NW, NE, SE]
        self.color = color

class Square(Rectangle):
    def __init__(self, width, center=Vector(0, 0), color = 'black'):
        Rectangle.__init__(self, width, width, center, color)
        
class Circle(Shape):
    def __init__(self, center = Vector(0, 0), radius = 10, color = 'black'):
        self.center = center
        self.radius = radius
        self.color = color

    def render(self):
        turtle.penup()
        turtle.setposition(self.center.x, self.center.y - self.radius)
        turtle.pendown()
        turtle.fillcolor(self.color)
        turtle.pencolor(self.color)
        turtle.begin_fill()
        turtle.circle(self.radius)
        turtle.end_fill()

    def rotate(self, theta):
        '''Theta is in degrees.'''
        theta = math.radians(theta)
        RotationMatrix = Matrix(math.cos(theta), -1*math.sin(theta), math.sin(theta), math.cos(theta))        
        self.center = RotationMatrix * self.center

    def translate(self, x, y):
        self.center.x = self.center.x + x
        self.center.y = self.center.y + y

class Triangle(Shape):
    def __init__(self, height, base, center = Vector(0, 0), color = 'black'):
        ''' Creates a right triangle starting at (0,0)
            Args: height = length of vertical leg
                  base = length of horizontal leg'''
        N = Vector(center.x, center.y + height)
        S = Vector(center.x, center.y)
        E = Vector(center.x + base, center.y)
        self.points = [N, S, E]
        self.color = color
        self.center = center


        
