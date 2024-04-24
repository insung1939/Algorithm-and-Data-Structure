#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
#include "linked_list.h"

int main() {
    TrieNode *root = trie_createNode();  // Create the root node of the Trie
    loadWordsFromFile(root, "dp-words.txt");  // Load words from file into the Trie

    char prefix[100];
    printf("Enter a prefix to predict words: ");
    scanf("%s", prefix);

    if (strlen(prefix) <= 2) {
        printf("Prefix must be longer than 2 characters.\n");
        trie_free(root);
        return 0;
    }

    ListNode *listHead = createNode("");  // Create a dummy head node for the linked list

    printf("Predictions for '%s':\n", prefix);
    predict(root, prefix, listHead);  // Predict words starting with the given prefix

    printf("\nReported Predictions:\n");
    displayList(listHead);  // Display the predicted words using the linked list

    // Free memory allocated for the Trie and linked list
    trie_free(root);
    freeList(listHead);

    return 0;
}
