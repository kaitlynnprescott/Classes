"""
Name          : largestrectangle.py
Author        : Matthew Crepea / Brian S. Borowski
Version       : 1.0
Date          : March 31, 2018
Last modified : April 1, 2018
Description   : Solution to HackerRank -> Data Structures -> Stacks ->
                Largest Rectangle
                https://www.hackerrank.com/challenges/largest-rectangle/problem
"""
def largest_rectangle(heights):
    """
    Iterate through the list of heights, adding successively larger elements to
    the stack.
    We store elements on the stack in the form (height, index) where height is
    the height of the building and index is where it resides in the list.

    When we find a building that is less than or equal to the height of the last
    building, we begin popping elements off the top of the stack that are taller
    than the new building, and we calculate the 'popped' elements' areas.
    In this case, area is defined as width * height, where
       - height is simply the height of the building in question and
       - width is the width of the rectangle.
       
    After we have iterated over all elements in the list, finish by popping the
    remaining elements off the stack and calculating their areas.
    """
    max_area = 0
    stack = [ (heights[0], 0) ]
    for i in range(1, len(heights)):
        if heights[i] > heights[i - 1]:
            stack.append( (heights[i], i) )
        else:
            popped_index = None
            while stack and stack[-1][0] > heights[i]:
                popped_element = stack.pop()
                popped_index = popped_element[1]
                max_area = \
                    max(max_area, popped_element[0] * (i - popped_element[1]))
            if popped_index != None:
                stack.append( (heights[i], popped_index) )
            else:
                stack.append( (heights[i], i) )
    while stack:
        popped_element = stack.pop()
        max_area = \
            max(max_area, popped_element[0] * (len(heights) - popped_element[1]))
    return max_area

if __name__ == '__main__':
    _ = int(input().strip())
    heights = list(map(int, input().strip().split(' ')))
    print(largest_rectangle(heights))
