#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"
#include "linked_list.h"
#include <assert.h>

// Function to create a new TrieNode
TrieNode *trie_createNode(void) {
    TrieNode *root = (TrieNode *)malloc(sizeof(TrieNode));
    assert(root != NULL);  // Ensure memory allocation was successful
    if (!root) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    root->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        root->children[i] = NULL;
    }
    return root;
}


// Function to create a new ListNode
ListNode *list_createNode(const char *word) {
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));  // Allocate memory for the node
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");  // Print error message if allocation fails
        exit(EXIT_FAILURE);  // Terminate program
    }
    strcpy(newNode->word, word);  // Copy the word to the node
    newNode->next = NULL;  // Initialize next pointer to NULL
    return newNode;  // Return the newly created node
}

// Function to print all words in the Trie starting with a given prefix
void printWords(TrieNode *root, char *wordArray, int pos, ListNode *listHead) {
    if (root->isEndOfWord) {  // If the current node marks the end of a word
        wordArray[pos] = '\0';  // Terminate the word
        ListNode *newNode = list_createNode(wordArray);  // Create a new ListNode
        newNode->next = listHead->next;  // Insert the new node at the beginning of the list
        listHead->next = newNode;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {  // If the child node exists
            wordArray[pos] = i + 'a';  // Append the character to the word
            printWords(root->children[i], wordArray, pos + 1, listHead);  // Recursively print words
        }
    }
}

// Function to predict words starting with a given prefix
void predict(TrieNode *root, const char *prefix, ListNode *listHead) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(prefix); level++) {
        int index = prefix[level] - 'a';  // Calculate the index of the current character
        if (!pCrawl->children[index]) {  // If no words match the prefix
            printf("No word found with the prefix '%s'\n", prefix);
            return;
        }
        pCrawl = pCrawl->children[index];  // Move to the next node
    }
    char wordArray[100];
    strcpy(wordArray, prefix);  // Copy the prefix to the word array
    printWords(pCrawl, wordArray, strlen(prefix), listHead);  // Print words starting with the prefix
}

// Function to free memory allocated for the Trie
void trie_free(TrieNode *root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            trie_free(root->children[i]);  // Recursively free memory for child nodes
    free(root);  // Free memory for the current node
}

// Function to insert a word into the Trie, filtering out non-alphabet characters
void insertFiltered(TrieNode *root, const char *key) {
    TrieNode *pCrawl = root;
    for (int level = 0; level < strlen(key); level++) {
        if (key[level] >= 'a' && key[level] <= 'z') {  // Check if the character is a lowercase alphabet
            int index = key[level] - 'a';  // Calculate the index of the current character
            if (!pCrawl->children[index])  // If the child node doesn't exist
                pCrawl->children[index] = trie_createNode();  // Create a new node
            pCrawl = pCrawl->children[index];  // Move to the next node
        }
    }
    pCrawl->isEndOfWord = true;  // Mark the end of the word
}

// Function to load words from a file into the Trie
void loadWordsFromFile(TrieNode *root, const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file in read mode
    if (!file) {
        perror("Failed to open the file");  // Print error message if file opening fails
        exit(EXIT_FAILURE);  // Terminate program
    }
    char word[100];
    while (fscanf(file, "%s", word) == 1) {  // Read words from the file
        insertFiltered(root, word);  // Insert each word into the Trie
    }
    fclose(file);  // Close the file
}
