/************************************************************************************
 * Name        : contacts.c
 * Author      : Kaitlynn Prescott, Christopher Rudel, Meng Qiu
 * Date        : Feb 12, 2018
 * Description : HackerRank Trie-- Contacts
 * Pledge      : I pledge my honor that I have abided by the Stevens honor system.
 ************************************************************************************/

#define ALPHABET_LENGTH    26
#define OPERATION_BUF_SIZE  5
#define NAME_BUF_SIZE      22
#define MAXCHAR 1000
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/* Basic trie node -- also, keep track of number of nodes below this one. */
typedef struct node {
    int num_children;
    struct node* children[ALPHABET_LENGTH];
} trie_node;

trie_node makeTrie() {
    trie_node *T = malloc(sizeof(trie_node));
    T->num_children = 0;
    for (int i = 0; i < 26; i++) {
        T->children[i] = malloc(sizeof(trie_node));
    }
    return *T;
}

//add each word in the Trie
void addOneNode(trie_node *tree, char* input) {
    char curr = input[0];
    int currInd = ((int)curr-97);
    if (curr == '\0') {
        tree->num_children += 1;
    } else if (tree->children[currInd] != NULL) {
        tree->num_children += 1;
        addOneNode(tree->children[currInd], &input[1]);
    } else {
        trie_node *newNode;
        newNode = malloc(sizeof(trie_node));
        tree->children[currInd] = newNode;
        tree->num_children += 1;
        addOneNode(tree->children[currInd], &input[1]);
    }
}

//build a whole trie from all words.
void addAllNodes(char** input) {
    trie_node T = makeTrie();
    for (int i = 0; i < sizeof(input); i++) {
        addOneNode(&T, input[i]);
    }
}

int countPrefix(trie_node *tree, char* prefix) {
    char curr = prefix[0];
    int currInd = ((int)curr-97);
    if (curr == '\0') {
        return tree->num_children;
    } else if (tree->children[currInd] == NULL) {
        return 0;
    } else {
        return countPrefix(tree->children[currInd], &prefix[1]);
    }
}


int main() {
    int n;
    trie_node tri = makeTrie();
    // get number of commands
    scanf("%d", &n);
    for (int a0=0; a0<n; a0++) {
        // set first input to op (operation)
        char* op = (char *)malloc(1000*sizeof(char));
        // set second input to contact (name/partial)
        char* contact = (char *)malloc(1000 * sizeof(char));
        scanf("%s %s", op, contact);
        if (op != NULL && contact == NULL) {
            // not enough input given
            printf("Must enter an operation and contact.");
            return 1;
        }
        if (strcmp(op, "add") == 0) {
            // add contact to tree
            addOneNode(&tri, contact);
        }
        if (strcmp(op, "find") == 0) {
            // count how many contacts have prefix contact
            int ret;
            ret = countPrefix(&tri, contact);
            printf("%d\n", ret);
        }
    }
    return 0;
}


