def create_row(width):
    row = ['|']
    for col in range(width):
        row += [' |']
        return row

def last_row(width):
    for i in range(width):
        row += [' i']

def create_board(width, height):
    A = []
    for row in range(height):
        A += [create_row(width)]
    A += ['-'] * width + 1
    A += [last_row(width)]
    return A
        
