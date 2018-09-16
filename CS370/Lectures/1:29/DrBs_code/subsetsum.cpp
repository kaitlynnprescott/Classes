/*******************************************************************************
 * Name        : subsetsum.cpp
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : April 6, 2015
 * Description : Solution to
 *               https://www.urionlinejudge.com.br/judge/en/runs/add/1690
 ******************************************************************************/
#include <algorithm>
#include <cstdio>

using namespace std;

/**
 * Computes the sum of values in the array.
 */
int sum(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

/**
 * Dynamic programming approach to subset sum problem in pseudo-polynomial time.
 * Works well with an array of small values.
 */
int smallest_impossible(int array[], int size) {
    int lookup_size = sum(array, size) + 2; // Account for index 0 and 1 larger
                                            // than the largest possible sum.
    bool *sums = new bool[lookup_size];

    sums[0] = true;
    for (int i = 1; i < lookup_size; i++) {
        sums[i] = false;
    }

    for (int i = 0; i < size; i++) {
        for (int j = lookup_size - 1; j >= array[i]; j--) {
            sums[j] = sums[j] || sums[j - array[i]];
        }
    }
    int answer = 0;
    for (int i = 1; i < lookup_size; i++) {
        if (!sums[i]) {
            answer = i;
            break;
        }
    }
    delete [] sums;
    return answer;
}

/**
 * Fast way to read integers from standard in.
 */
inline int next_int() {
    register int c, value;
    c = getchar_unlocked();
    value = 0;
    do {
        value = value * 10 + (c & 15);
        c = getchar_unlocked();
    } while (c >= 33);
    return value;
}

/**
 * Finds the first sum that is not possible to create from the positive integers
 * in the array.
 */
long long smallest_impossible2(int array[], int size) {
    // Sorting is critical!
    sort(array, array + size);
    // A long long is needed as regular a long might actually be the same size
    // as an int (depending on the system).
    long long smallest = 1;
    for (int i = 0; i < size; i++) {
        if (array[i] <= smallest) {
            smallest += array[i];
        } else {
            break;
        }
    }
    return smallest;
}

int main() {
    int num_test_cases = next_int();
    int *array = new int[10000];
    for (int i = num_test_cases - 1; i >= 0; i--) {
        int array_size = next_int();
        for (int j = 0; j < array_size; j++) {
            array[j] = next_int();
        }
        printf("%lld\n", smallest_impossible2(array, array_size));
    }
    delete [] array;
    return 0;
}
