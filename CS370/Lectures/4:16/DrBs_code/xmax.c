/**
 * xmax.c
 * Matthew Crepea / Brian Borowski
 * Code to solve the SPOJ XMAX problem: http://www.spoj.com/submit/XMAX/
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Returns highest bit placement of long long x.
 */
int highest_bit_ind(long long x) {
    int count = 0;
    while (x > 1) {
        x >>= 1;
        count++;
    }
    return count;
}

int main() {
    int num_lines, i, highest_bit;
    long long max_val, result = 0;
    long long* input;

    /* Allocate and read input. */
    scanf("%d", &num_lines);
    input = (long long*)calloc(num_lines, sizeof(long long));
    for (i = 0; i < num_lines; ++i) {
        scanf("%lli", &input[i]);
    }

    while (1) {
        /* Find the max value in the array. If it is 0, break the loop. */
        max_val = input[0];
        for (i = 1; i < num_lines; ++i) {
            if (input[i] > max_val) {
                max_val = input[i];
            }
        }
        if (max_val == 0) {
            break;
        }

        /* Set highest bit to the highest bit of max_val. */
        highest_bit = highest_bit_ind(max_val);

        /* Iterate through the array; set all values who have same common bit
         * to (value^max_val).
         * If statement finds all elements that have highest bit in common
         * with max_val and then xors them. */
        for (i = 0; i < num_lines; ++i) {
            if (input[i] >> highest_bit) {
                input[i] ^= max_val;
            }
        }

        /* If highest bit is not set in result, then add in the maxval to
         * result. */
        if ( !((result >> highest_bit) & 1) ) {
            result ^= max_val;
        }
    }

    printf("%lli\n", result);
    free(input);
    return 0;
}
