/*******************************************************************************
 * Name          : contacts.c
 * Author        : Brian S. Borowski
 * Version       : 1.0
 * Date          : March 28, 2016
 * Last modified : March 31, 2017
 * Description   : Solves HackerRank's 'Contacts' problem using a trie.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_LENGTH    26
#define OPERATION_BUF_SIZE  5
#define NAME_BUF_SIZE      22

/* Basic trie node -- also, keep track of number of nodes below this one. */
typedef struct node {
    int         prefix_count;
    struct node *children[ALPHABET_LENGTH];
} trie_node;

/**
 * Instantiates a node on the heap.
 */
trie_node *create_node() {
    /* Return 1 block of size sizeof(trie_node) initialized to 0. */
    return (trie_node*)calloc(1, sizeof(trie_node));
}

/**
 * Inserts a string into the trie.
 * For each node we pass while inserting the string, increment its prefix count
 * count so that we can access this information quickly when finding matches.
 */
void insert(trie_node *n, char *str) {
    int index;
    while (*str) {
        index = *str - 'a';
        trie_node *child = n->children[index];
        if (!child) {
            child = create_node();
            n->children[index] = child;
        }
        child->prefix_count++;
        str++;
        n = child;
    }
}

/**
 * Traverse the trie until we run out of characters or come to a NULL node. If
 * we run out of characters, return the count at the node. Otherwise, the
 * string is not in the trie, and we return 0.
 */
int find(trie_node *n, char *str) {
    while (*str && n) {
        n = n->children[*str++ - 'a'];
    }
    return n != NULL ? n->prefix_count : 0;
}

/**
 * Free the memory we've allocated.
 */
void clean_up(trie_node *node) {
    int i;
    if (node == NULL) {
        return;
    }
    for (i = 0; i < ALPHABET_LENGTH; i++) {
        clean_up(node->children[i]);
    }
    free(node);
}

int main() {
    int       operations;
    char      operation[OPERATION_BUF_SIZE];
    char      name[NAME_BUF_SIZE];
    trie_node *root = create_node();

    scanf("%d", &operations);
    while (operations-- > 0) {
        scanf("%s %s", operation, name);

        /* Insert if the first word is "add", otherwise find and print the
           number of matches. */
        if (strcmp(operation, "add") == 0) {
            insert(root, name);
        } else {
            printf("%d\n", find(root, name));
        }
    }

    clean_up(root);
    return 0;
}
