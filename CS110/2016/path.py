
def path(x, y, l):
    if l == []:
        return []
    elif (x, y) == l[0]:
        return True
    else:
        useit = l[0], path(x, y, l[1:])
        loseit = path(x, y, l[1:])
        return (useit, loseit)
    

#print salaryUpdate([("sam", 70000), ("amy", 80000)])
        

        
print path('A', 'B', [])
print path('D', 'A', [('A', 'B'), ('B','A'), ('C','B'), ('B','D')])
print path('A', 'D', [('A', 'B'), ('B','A'), ('C','B'), ('B','D')])
