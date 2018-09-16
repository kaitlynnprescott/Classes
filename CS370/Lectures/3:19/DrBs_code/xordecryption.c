/*******************************************************************************
 * Name        : xordecryption.c
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : March 23, 2015
 * Description : Solution to Project Euler #59
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 4096
#define THRESHOLD    0.95

char *original, *copy;
int num_chars, required_chars;

/**
 * Grows the array to the new size via realloc().
 * See http://www.cplusplus.com/reference/cstdlib/realloc/ for more details.
 */
int* grow_array(int *array, int new_size) {
    int *more_ascii_values = (int *)realloc(array, new_size * sizeof(int));
    if (more_ascii_values != NULL) {
        return more_ascii_values;
    }
    free(array);
    return NULL;
}

void display_text() {
    int i;
    for (i = 0; i < num_chars; i++) {
        printf("%c", copy[i]);
    }
    printf("\n");
}

int get_ascii_sum() {
    int i, sum = 0;
    for (i = 0; i < num_chars; i++) {
        sum += copy[i];
    }
    return sum;
}

int try_key(char key[]) {
    int i = 0, j = 0, count = 0;
    char c;

    while (i < num_chars) {
        c = copy[i] = (char)(original[i] ^ key[j]);
        i++;
        j++;
        if (j == 3) {
            j = 0;
        }
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') || c == ' ' || c == '.') {
            count++;
        }
    }

    if (count >= required_chars) {
        printf("key = %s, sum = %d: ", key, get_ascii_sum());
        display_text();
        return 1;
    }
    return 0;
}

int main() {
    int *ascii_values = (int *)malloc(DEFAULT_SIZE * sizeof(int));
    int i, t = 0, size = DEFAULT_SIZE;
    char c, x, y, z;
    char key[4];

    FILE *input_file = fopen("cipher.txt", "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error: Cannot read file 'cipher.txt'.\n");
        return 1;
    }

    while ((c = getc(input_file)) != EOF) {
        if (c == ',' || c == '\n') {
            if (num_chars >= size) {
                size *= 2;
                ascii_values = grow_array(ascii_values, size);
                if (ascii_values == NULL) {
                    fprintf(stderr,
                            "Error: Cannot allocate array of %d integers.\n",
                            size);
                    return 1;
                }
            }
            ascii_values[num_chars++] = t;
            t = 0;
        } else {
            t = t * 10 + (c - '0');
        }
    }
    fclose(input_file);

    original = (char *)malloc(num_chars * sizeof(char));
    copy = (char *)malloc(num_chars * sizeof(char));
    for (i = 0; i < num_chars; i++) {
        original[i] = (char)ascii_values[i];
    }

    required_chars = (int)(THRESHOLD * num_chars);
    // I am treating the 3-character key as a null-terminated string. By doing
    // so, I have the ability to print it and use functions in string.h.
    key[3] = '\0';
    for (x = 'a'; x <= 'z'; x++) {
        key[0] = x;
        for (y = 'a'; y <= 'z'; y++) {
            key[1] = y;
            for (z = 'a'; z <= 'z'; z++) {
                key[2] = z;
                if (try_key(key)) {
                    // Ah! A goto statement. I do not mind a goto now and then,
                    // as long as the label is below the goto. This design can
                    // be used successfully as an error handler in C, where
                    // a function needs to free up memory it allocated before
                    // an unrecoverable error occurred. Still, some people
                    // despise the use of goto. Decide for yourself, but just
                    // keep your code readable.
                    // Check out the C++ version to see how you can eliminate
                    // the use of goto.
                    goto cleanup;
                }
            }
        }
    }

cleanup:
    free(ascii_values);
    free(original);
    free(copy);

    return 0;
}
