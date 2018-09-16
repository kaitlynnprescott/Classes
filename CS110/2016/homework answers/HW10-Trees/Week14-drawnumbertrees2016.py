#drawing leaves and simple nodes


import turtle

branchLen =50


def drawLeaf(n,t):
    "takes a leaf and a turtle and draws it"
    t.write(n[0], font=("Arial", 16, "normal"))



def drawTree(n,t):
    "takes a tree and a turtle and draws it"
    t.ht() #hide turtle
    if n[1] == ():
        drawLeaf(n,t)
    else:
        t.write(n[0], font=("Arial", 16, "normal"))
        t.left(30)
        t.forward(branchLen)
        drawTree(n[1],t)
        t.backward(branchLen)
        t.right(60)
        t.forward(branchLen)
        drawTree(n[2],t)
        t.backward(branchLen)
        t.left(30)

       
    
def main():
    t = turtle.Turtle()
    myWin = turtle.Screen()
    t.color("blue")
    drawTree(('1',
                  ('2',
                       ('3', (), ()),
                       ('4', (), ())) ,
                  ('5',
                       ('9',
                            ('6', (), ()),
                            ('7', (), ())) ,
                       ('4',
                            ('5', (), ()),
                            ('6', (), ())))),t)            
    myWin.exitonclick()
    

main()


# can you draw this tree?

#('root', ('root', (3, (), ()), (4, (), ())) , ('root', (1, (), ()), (2, (), ())) )

#    drawTree(("root", (4, (), ()) , (3, (), ())),t)
