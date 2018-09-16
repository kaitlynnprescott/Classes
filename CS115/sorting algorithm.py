def swap (lst, a, b):
    temp = lst[a]
    lst[a] = lst[b]
    lst[b] = temp


def selectionSort(lst):
    n = len(lst)
    for i in range(n - 1):
        minIndex = i
        for j in range(i + 1, n):
            if lst[j] < lst[minIndex]:
                minIndex = j
        if i != minIndex:
            swap(lst, i, minIndex)

lst = [6, 3, 5, 8, 9, 7, 10]
selectionSort(lst)
print lst
