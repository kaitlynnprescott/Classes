/*******************************************************************************
 * Name          : hashit.c
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : January 22, 2017
 * Last modified : February 14, 2017
 * Description   : Solution to SPOJ HASHIT - Hash it!
 *                 http://www.spoj.com/problems/HASHIT/
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE     101
#define MAX_COLLISIONS  20
#define MAX_KEY_LENGTH  15

typedef struct {
    char* keys[TABLE_SIZE];
    int num_keys;
} hash_set;

/**
 * Makes a copy of a string.
 * Apparently SPOJ no longer supports the POSIX-compliant strdup function.
 */
char *str_dup(char *str) {
    int len = strlen(str);
    char *copy = (char *)malloc(sizeof(char) * (len + 1));
    if (copy) {
        strncpy(copy, str, len);
        copy[len] = '\0';
    }
    return copy;
}

/**
 * Removes all elements from the hash set.
 */
void clear_table(hash_set *set) {
    int i;
    for (i = 0; i < TABLE_SIZE; ++i) {
        if (set->keys[i]) {
            free(set->keys[i]);
            set->keys[i] = NULL;
        }
    }
    set->num_keys = 0;
}

/**
 * Computes the hash of a string, according to the problem description.
 */
int hash(char *key) {
    int hash = 0, index = 1;
    while (*key) {
        /* Dereference and then increment -- *key++ */
        hash += *key++ * index++;
    }
    return 19 * hash % TABLE_SIZE;
}

/**
 * Probes up to MAX_COLLISIONS times to find a key in the hash set. Returns the
 * index of the key, if it is found, and -1 otherwise.
 * Note: This function takes as argument the hash code to save time in the
 * insert and delete methods.
 */
int find_key_hash(hash_set *set, char *key, int hash_code) {
    int i, index;
    for (i = 0; i < MAX_COLLISIONS; ++i) {
        index = (hash_code + i * i + 23 * i) % TABLE_SIZE;
        if (set->keys[index] && strcmp(set->keys[index], key) == 0) {
            return index;
        }
    }
    return -1;
}

/**
 * Searches the hash set for the key.
 * Returns the index of the key, if it is found, and -1 otherwise.
 */
int find_key(hash_set *set, char *key) {
    return find_key_hash(set, key, hash(key));
}

/**
 * Inserts the key into the hash set.
 * Returns the index of the key, if insertion is successful, and -1 otherwise.
 */
int insert_key(hash_set *set, char *key) {
    int i, index, hash_code = hash(key);
    if ((index = find_key_hash(set, key, hash_code)) >= 0) {
        return index;
    }
    for (i = 0; i < MAX_COLLISIONS; ++i) {
        index = (hash_code + i * i + 23 * i) % TABLE_SIZE;
        if (!set->keys[index]) {
            set->keys[index] = key;
            ++set->num_keys;
            return index;
        }
    }
    return -1;
}

/**
 * Deletes the key from the hash set.
 * Returns the index of the key, if deletion is successful, and -1 if the
 * key is not found.
 */
int delete_key(hash_set *set, char *key) {
    int index, hash_code = hash(key);
    if ((index = find_key_hash(set, key, hash_code)) >= 0) {
        free(set->keys[index]);
        set->keys[index] = NULL;
        --set->num_keys;
    }
    return index;
}

/**
 * Displays index-key pairs present in the hash set.
 */
void display_keys(hash_set *set) {
    int i;
    for (i = 0; i < TABLE_SIZE; ++i) {
        if (set->keys[i]) {
            printf("%d:%s\n", i, set->keys[i]);
        }
    }
}

int main() {
    char buf[MAX_KEY_LENGTH + 5];
    int i, j, num_test_cases, num_operations;
    hash_set set;
    memset(&set, 0, sizeof(hash_set));

    scanf("%d", &num_test_cases);
    for (i = 0; i < num_test_cases; ++i) {
        scanf("%d", &num_operations);
        for (j = 0; j < num_operations; ++j) {
            scanf("%s", buf);
            if (strncmp(buf, "ADD", 3) == 0) {
                insert_key(&set, str_dup(buf + 4));
            } else {
                delete_key(&set, buf + 4);
            }
        }
        printf("%d\n", set.num_keys);
        display_keys(&set);
        clear_table(&set);
    }
    return 0;
}
