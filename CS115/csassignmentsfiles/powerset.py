'''
Created on Feb 11, 2015

@author: O816
'''
def powerset(lst):
    if lst == []:
        return [[]]
    lose_it = powerset(lst[1:])
    use_it = map(lambda subset: [lst[0]] + subset, lose_it)
    return lose_it + use_it

print powerset([1])
print powerset([1, 2])
print powerset([1, 2, 3])
print powerset(['a', 'b', 'c'])

def subset(target, lst):
    if target == 0:
        return True
    if lst == []:
        return False
    use_it = subset(target - lst[0], lst[1:])
    lose_it = subset(target, lst[1:])
    return use_it or lose_it 

def subset_with_values(target, lst):
    if target == 0:
        return [True, []]
    if lst == []:
        return [False, []]
    use_it = subset_with_values(target - lst[0], lst[1:])
    if use_it[0]:
        return [True, use_it[1] + [lst[0]]]
    return subset_with_values(target, lst[1:])

print subset_with_values(10, [12,  2, 8, 4, 3, 1])
