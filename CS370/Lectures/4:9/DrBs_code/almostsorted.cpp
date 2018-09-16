/*******************************************************************************
 * Name        : almostsorted.cpp
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : March 30, 2015
 * Description : Solution to HackerRank -> Sorting -> Almost Sorted
 ******************************************************************************/
#include <iostream>

using namespace std;

enum result_t { NO, SWAP, REVERSE, SORTED };

int directive, start_index, end_index;

result_t is_swappable(int array[], int length) {
    int num_inversions = 0;
    start_index = end_index = -1;
    for (int i = 1; i < length; ++i) {
        if (array[i - 1] > array[i]) {
            if (num_inversions == 0) {
                // First inversion seen; record starting index.
                start_index = i - 1;
            } else if (num_inversions == 1) {
                // Inversion already seen; record ending index.
                end_index = i;
            } else {
                // Too many inversions; swapping not possible.
                return NO;
            }
            ++num_inversions;
        } else if (num_inversions > 0 && end_index == -1) {
            // Inversion not found; record ending index of previously found
            // inversion.
            end_index = i - 1;
        }
    }
    if (num_inversions == 0) {
        return SORTED;
    }
    if (end_index == -1) {
        // If ending index was not found, set it to the last index in the array.
        end_index = length - 1;
    }
    // Determine if swapping is possible.
    if ((end_index == length - 1 || array[start_index] <= array[end_index + 1]) &&
        (start_index == 0 || array[end_index] >= array[start_index - 1])) {
        return SWAP;
    }
    return NO;
}

result_t is_reversible(int array[], int length) {
    int num_groups = 0; // Number of groups found to be in reverse.
    start_index = end_index = -1;
    for (int i = 1; i < length; ++i) {
        if (array[i - 1] > array[i]) {
            // An inversion has been found.
            if (num_groups > 0) {
                // A group has already been found, so reversing is not possible.
                return NO;
            }
            // Record starting index.
            start_index = i - 1;
            ++i;
            // Look for the end of this inversion.
            while (i < length && array[i - 1] > array[i]) {
                ++i;
            }
            // Record ending index.
            end_index = i - 1;
            ++num_groups;
        }
    }
    // Determine if reversing is possible.
    // Consider [1 2 5 4 1], [5 4 1 2 3], [5 4 1 6 7], [1 2 5 4 2 6 7].
    if ((end_index == length - 1 || array[start_index] <= array[end_index + 1]) &&
        (start_index == 0 || array[end_index] >= array[start_index - 1])) {
        return REVERSE;
    }
    return NO;
}

int main() {
    // Speed up input with little effort.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int length;
    cin >> length;
    
    int array[length];
    for (int i = 0; i < length; ++i) {
        cin >> array[i];
    }
    
    result_t result = is_swappable(array, length);
    if (result == SORTED) {
        cout << "yes" << endl;
    } else if (result == SWAP) {
        cout << "yes" << endl << "swap " << start_index + 1 << " "
             << end_index + 1 << endl;
    } else if (is_reversible(array, length) == REVERSE) {
        cout << "yes" << endl << "reverse " << start_index + 1 << " "
             << end_index + 1 << endl;
    } else {
        cout << "no" << endl;
    }
    return 0;
}
