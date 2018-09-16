"""
Name          : connectedcells.py
Author        : Matthew Crepea / Brian S. Borowski
Version       : 1.1
Date          : April 8, 2018
Last modified : April 11, 2018
Description   : Solution to HackerRank -> Algorithms -> Search ->
                Connected Cells in a Grid

https://www.hackerrank.com/challenges/connected-cell-in-a-grid/problem
"""

def count_cells_in_region(matrix, row, col):
    """
    Counts cells in the region in matrix, which includes the cell at [row, col].
    Zeros out all elements of the region in the matrix while counting.
    """
    cell_count = 0
    m = len(matrix)
    n = len(matrix[0])
    frontier = [[row, col]]
    while frontier:
        point = frontier.pop()
        x, y = point[0], point[1]
        if matrix[x][y]:
            matrix[x][y] = 0
            cell_count += 1
        for i in range(x - 1, x + 2):
            if i >= 0 and i < m:
                for j in range(y - 1, y + 2):
                    if j >= 0 and j < n and matrix[i][j]:
                        matrix[i][j] = 0
                        cell_count += 1
                        frontier.append([i, j])
    return cell_count

def max_connected_cells(matrix):
    """Iterates over the matrix, looking for regions.
    When a region is detected, computes the count of cells in the region and
    zeros out the elements.
    Returns the size of the largest region.
    """
    max_region = 0
    for row in range(len(matrix)):
        for col in range(len(matrix[0])):
            if matrix[row][col]:
                count = count_cells_in_region(matrix, row, col)
                if count > max_region:
                    max_region = count
    return max_region

if __name__ == '__main__':
    n = int(input().strip())
    _ = int(input().strip())
    matrix = []
    for _ in range(n):
        matrix_row = [int(cell) for cell in input().strip().split(' ')]
        matrix.append(matrix_row)
    print(max_connected_cells(matrix))
