
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
        pos = binary_search(sequence[i], sequence, increasing, 1, length)
        predecessor[i] = increasing[pos-1]
        increasing[pos] = i
        if pos > length:
            length = pos
    lis = [0] * length
    j = increasing[length]
    for i in range(length - 1, -1, -1):
        lis[i] = sequence[j]
        j = predecessor[j]
    return lis

print longest_increasing_subsequence([3,1,4,1,5,9,2])
