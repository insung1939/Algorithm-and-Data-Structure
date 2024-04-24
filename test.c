#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "linked_list.h"

int main() {
    TrieNode *root = trie_createNode();  // Create the root node of the Trie
    loadWordsFromFile(root, "dp-words.txt");  // Load words from file into the Trie

    // Test case: 'dogdogdog'
    char prefix[100];
    strcpy(prefix, "dogdogdog");
    printf("Predictions for '%s':\n", prefix);
    ListNode *listHead = createNode("");  // Create a dummy head node for the linked list
    predict(root, prefix, listHead);  // Predict words starting with the given prefix
    printf("\nReported Predictions:\n");
    displayList(listHead);
    freeList(listHead);  // Free memory allocated for the linked list

    // Test case: 'dog'
    strcpy(prefix, "dog");
    printf("\nPredictions for '%s':\n", prefix);
    listHead = createNode("");  // Create a dummy head node for the linked list
    predict(root, prefix, listHead);  // Predict words starting with the given prefix
    printf("\nReported Predictions:\n");
    displayList(listHead);
    freeList(listHead);  // Free memory allocated for the linked list

    // Free memory allocated for the Trie
    trie_free(root);

    return 0;
}
