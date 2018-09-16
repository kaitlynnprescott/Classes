""" Node is defined as
class node:
def __init__(self, data):
    self.data = data
    self.left = None
    self.right = None
"""

def helper(root, mini, maxi):
    if not root:
        return True
    data = root.data
    if data <= mini or data >= maxi:
        return false
    else:
        return helper(root.left, mini, data) and helper(root.right, data, maxi)
        

def check_binary_search_tree_(root):
    if not root:
        return True
    else:
        return helper(root.left, -1, root.data) and helper(root.right, root.data, 10001)    
    
