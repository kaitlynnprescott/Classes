
from bisect import bisect_left

def longestIncreasingSubsequence(arr):
    num_vals = len(arr)
    lis = [0] * (num_vals + 1)
    length = 0
    result = []

    for i in range(num_vals):
        if arr[i] > lis[length]:
            # append current
            pos = length + 1
            result.append(values[i])
        else:
            # Binary search for index of where current should be inserted
            pos = bisect_left(lis, arr[i], 1, length)
        lis[pos] = arr[i]
        if pos > length:
            length = pos
    return (length, lis[1:length + 1])


num_values = int(input())
values = [0] * num_values
for i in range(num_values):
    values[i] = int(input())
print (longestIncreasingSubsequence(values))
