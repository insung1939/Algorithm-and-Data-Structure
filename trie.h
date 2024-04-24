#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define ALPHABET_SIZE 26

// Forward declaration of ListNode structure
struct ListNode;

// Define the structure of a TrieNode if not defined
#ifndef TrieNode_defined
#define TrieNode_defined
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];  // Array of pointers to child nodes
    bool isEndOfWord;  // Flag to mark the end of a word
} TrieNode;
#endif

// Function to create a new TrieNode
TrieNode *trie_createNode(void);

// Function to predict words starting with a given prefix
void predict(TrieNode *root, const char *prefix, struct ListNode *listHead);

// Function to free memory allocated for the Trie
void trie_free(TrieNode *root);

// Function to insert a word into the Trie, filtering out non-alphabet characters
void insertFiltered(TrieNode *root, const char *key);

// Function to load words from a file into the Trie
void loadWordsFromFile(TrieNode *root, const char *filename);

#endif
