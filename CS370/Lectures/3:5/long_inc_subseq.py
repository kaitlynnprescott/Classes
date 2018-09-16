
def binary_search(key, values, increasing, low, high):
    while low <= high:
        mid = low + (high-low) // 2
        if key > values[increasing[mid]]:
            low = mid + 1
        else:
            high = mid - 1
    return low


def longest_increasing_subsequence(sequence):
    num_values = len(sequence)
    length = 0
    increasing = [None] * (num_values + 1)
    predecessor = [None] * num_values

    for i in range(num_values):
        if sequence[i] > increasing[length]:
            pos = length + 1
            predecessor[i] = sequence[i]
        else:
            pos = binary_search(sequence[i], sequence, increasing, 1, length)
        increasing[pos] = sequence[i]
        if pos > length:
            length = pos
    return increasing[1:length+1]

## something is wrong... don't know what... look at Dr. B's code

print longest_increasing_subsequence([3,1,4,1,5,9,2])
